#include "ParamEstimator.h"
#include <iostream>

CParamEstimator::CParamEstimator():
    Method(LS), pParam(nullptr), pVec(nullptr)
{
    pMatVar = new fMatrix();
}

CParamEstimator::~CParamEstimator()
{
    if (pMatVar)
    {
        delete pMatVar;
    }
}

void CParamEstimator::SetParamEstiMethod(ParamEstiMethod Method)
{
    this->Method = Method;
}

void CParamEstimator::SetMethodParameters(ParamEstiMethod Method, void* pParam)
{
    this->Method = Method;
    this->pParam = pParam;
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
    LS_Param* param = (LS_Param *) pParam;
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
    WLS_Param* param = (WLS_Param *) pParam;
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
    ML_Param* param = (ML_Param *) pParam;
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