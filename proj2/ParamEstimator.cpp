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

fMatrix* CParamEstimator::LeastSquares(fVector* pfVecOptParam)
{
    // parse parameter
    LS_Param* param = (LS_Param *) pParam;
    fMatrix matH  = *(param->pMat_H);
    fMatrix matHt = Transp(matH);
    fVector vecZ  = *(param->pVec_Z);

    // compute Inverse(Ht * H)
    fMatrix invHtH = Inverse(matHt * matH);

    // vector of parameter for output
    *pfVecOptParam = invHtH * matHt * vecZ;
    fVector v = vecZ - matH * *pfVecOptParam;
    v = v - Mean(v);
    fMatrix Vv = fMatrix(v) * fMatrix(v, RowVec) / (v.Size() - 1);
    Vv = Diag(Diag(Vv));

    *pMatVar = invHtH * matHt * Vv * matH * invHtH;
    return pMatVar;
}

fMatrix* CParamEstimator::WeightedLeastSquares(fVector* pfVecOptParam)
{
    return nullptr;
}

fMatrix* CParamEstimator::MaximumLikelihood(fVector* pfVecOptParam)
{
    return nullptr;
}