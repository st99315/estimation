#include "ParamEstimator.h"
#include <iostream>
#include <cmath>

CParamEstimator::CParamEstimator():
    Method(LS), pParam(nullptr), pVec(nullptr)
{
    pMatVar = new fMatrix();
}

CParamEstimator::~CParamEstimator()
{
    delete pMatVar;
}

void CParamEstimator::SetParamEstiMethod(ParamEstiMethod Method)
{
    this->Method = Method;
}

void CParamEstimator::SetMethodParameters(ParamEstiMethod Method, void* pParam)
{
    switch (Method)
    {
    case LS:
        ls_param = *((LS_Param *)pParam);
        this->pParam = &ls_param;
        break;

    case WLS:
        wls_param = *((WLS_Param *)pParam);
        this->pParam = &wls_param;
        break;

    case ML:
        ml_param = *((ML_Param *)pParam);
        this->pParam = &ml_param;
    }
    this->Method = Method;
}

fMatrix* CParamEstimator::SolveOptParam(fVector* pfVecOptParam)
{
    switch (Method)
    {
    case LS:
        return LeastSquares(pfVecOptParam);
    case WLS:
        return WeightedLeastSquares(pfVecOptParam);
    case ML:
        return MaximumLikelihood(pfVecOptParam);
    }
}

fMatrix* CParamEstimator::LeastSquares(fVector* pOptParam)
{
    // parse parameter
    auto* param = (LS_Param *) pParam;
    fMatrix matH  = *(param->pMat_H);
    fMatrix matHt = Transp(matH);
    fVector vecZ  = *(param->pVec_Z);

    // compute Inverse(Ht * H)
    fMatrix invHtH = (matHt * matH).Inv();

    // vector of parameter for output (p_ls)
    *pOptParam = invHtH * matHt * vecZ;

    fVector v = vecZ - matH * *pOptParam;
    fMatrix Vv = Diag(Diag(Cov(v)));

    *pMatVar = invHtH * matHt * Vv * matH * invHtH;
    return pMatVar;
}

fMatrix* CParamEstimator::WeightedLeastSquares(fVector* pOptParam)
{
    // parse parameter
    auto* param = (WLS_Param *) pParam;
    fMatrix matH  = *(param->pMat_H);
    fMatrix matHt = Transp(matH);
    fMatrix matW  = *(param->pMat_W);
    fVector vecZ  = *(param->pVec_Z);

    // compute Inverse(Ht * H)
    fMatrix invHtWH = (matHt * matW * matH).Inv();

    // vector of parameter for output (p_ls)
    *pOptParam = invHtWH * matHt * matW * vecZ;

    // Optional	(for error-variance computing)
    if (param->pMat_Vz)
    {
        fMatrix matVv = *(param->pMat_Vz);
        *pMatVar = invHtWH * matHt * matW * matVv * matW * matH * invHtWH;
        return pMatVar;
    }
    return nullptr;
}

fMatrix* CParamEstimator::MaximumLikelihood(fVector* pOptParam)
{
    // parse parameter
    auto* param = (ML_Param *) pParam;
    fMatrix matH  = *(param->pMat_H);
    fMatrix matHt = Transp(matH);
    fVector vecZ  = *(param->pVec_Z);
    fMatrix matVz = *(param->pMat_Vz);

    // compute Inverse
    fMatrix matW = matVz.Inv();
    fMatrix invHtWH = (matHt * matW * matH).Inv();

    *pOptParam = invHtWH * matHt * matW * vecZ;
    *pMatVar = invHtWH;
    return pMatVar;
}

fMatrix generateTransMat(fMatrix& src)
{
    auto x_m = Mean(src.GetCol(0));
    auto y_m = Mean(src.GetCol(1));

    Float sum = 0;
    for (int i = 0; i < src.Rows(); i++)
    {
        sum += sqrt(pow(src.GetElem(i, 0) - x_m, 2) + pow(src.GetElem(i, 1) - y_m, 2));
    }
    Float s = sqrt(2.0) * src.Rows() / sum;

    Float trans[9] = {
        s,  0, -s * x_m,
        0,  s, -s * y_m,
        0,  0,  1
    };
    return fMatrix(trans, 3, 3);
}

fMatrix normalizeMat(fMatrix& src, fMatrix& trans)
{
    fMatrix res(src.Rows(), src.Cols());
    for (int i = 0; i < src.Rows(); i++)
    {
        // Getting row from matrix and mapping to vector
        fVector vec(0, 0, 1);
        vec.SetBlock(0, src.GetRow(i));

        res.SetRow(i, trans * vec);
    }
    return res;
}

void InitiHomographyEstimation(fMatrix& src, fMatrix& tar, fMatrix& out)
{
    auto transMatSrc = generateTransMat(src);
    auto transMatTar = generateTransMat(tar);
    auto normalMatSrc = normalizeMat(src, transMatSrc);
    auto normalMatTar = normalizeMat(tar, transMatTar);

    // Generate A and Z
    fMatrix ABarMat(src.Rows() * 2, 8);
    fVector ZVec(src.Rows() * 2);
    for (int i = 0; i < src.Rows(); i++)
    {
        Float normalSrcX = normalMatSrc.GetElem(i, 0);  // x
        Float normalSrcY = normalMatSrc.GetElem(i, 1);  // y
        Float normalTarX = normalMatTar.GetElem(i, 0);  // x
        Float normalTarY = normalMatTar.GetElem(i, 1);  // y
        Float twoRows[16] = {
            normalSrcX, normalSrcY, 1, 0, 0, 0, -normalTarX * normalSrcX, -normalTarX * normalSrcY,
            0, 0, 0, normalSrcX, normalSrcY, 1, -normalTarY * normalSrcX, -normalTarY * normalSrcY
        };
        ABarMat.SetBlock(i * 2, 0, 2, 8, fVector(twoRows, 16));
        ZVec.Array()[i * 2]     = normalTarX;
        ZVec.Array()[i * 2 + 1] = normalTarY;
    }
    // ABarMat.Show();
    // ZVec.Show();

    // Setting LS parameter
    LS_Param ls_param;
    ls_param.pMat_H = &ABarMat;
    ls_param.pVec_Z = &ZVec;

    // Optimal parameter
    fVector optParam;

    // Estimate parameter
    CParamEstimator pe;
    pe.SetMethodParameters(LS, &ls_param);
    pe.SolveOptParam(&optParam);

    // Resize
    optParam.SetSize(3 * 3);
    optParam.Array()[8] = 1.0;
    //optParam.Show();

    // Getting H bar matrix and calculation H matrix
    fMatrix HBarMat(optParam.Array(), 3, 3);
    out = Inverse(transMatTar) * HBarMat * transMatSrc;
}