/*
 *	fVector.cpp
 *
 *	Description:
 *		Basic vector class with some associated methods.
 *
 * 	History:
 *	 	Author			Date
 *		---------------------------
 *		youjun		 2017/03/08
 *
 */

#include "fVector.h"

int fVector::nVecCount = 0;

/*-------------------------------------------------------------------------*
 *  CONSTRUCTORS & DESTRUCTORS                                             *
 *-------------------------------------------------------------------------*/
/* Initinalize constructor */
fVector::fVector(int size /* = 0 */): size(size), elem(nullptr)
{
    if (size > 0)
    {
        elem = new Float [size];
        std::memset(elem, 0, sizeof(Float) * size);
        nVecCount++;
    }
}

/* Copy constructor */
fVector::fVector(const fVector& src): size(src.size), elem(nullptr)
{
    if (size > 0)
    {   
        elem = new Float [size];
        std::copy(src.elem, src.elem + size, elem);
        nVecCount++;
    }
}

/* Assign constructor */
fVector::fVector(const Float *x, int n): size(n), elem(nullptr)
{
    if (size > 0)
    {   
        elem = new Float [size]; 
        std::copy(x, x + size, elem);
        nVecCount++;
    }
}

fVector::fVector(int n, const Float* x): size(n), elem(nullptr)
{
    if (size > 0)
    {   
        elem = new Float [size]; 
        std::copy(x, x + size, elem);
        nVecCount++;
    }
}

fVector::fVector(Float x, Float y): size(2)
{
    elem = new Float [size]; 
    elem[0] = x;
    elem[1] = y;
    nVecCount++;
}

fVector::fVector(Float x, Float y, Float z): size(3)
{
    elem = new Float [size]; 
    elem[0] = x;
    elem[1] = y;
    elem[2] = z;
    nVecCount++;
}

/* Destructor */
fVector::~fVector()
{
    if (elem)
    {
        delete [] elem;
        elem = nullptr;
        nVecCount--;

#ifdef _DEBUG_CNT_
        std::cout << "nVecCount: " << nVecCount << std::endl;
#endif
    }
}

/*-------------------------------------------------------------------------*
 *  PUBLIC FUNCTIONS                                                       *
 *-------------------------------------------------------------------------*/

void fVector::Show(VecType Type /* = ColVec */) const
{
    using namespace std;
    cout << fixed << setprecision(SET_P);
    
    if (RowVec == Type)
    {
        for (int i = 0; i < size; i++)
            cout << setw(SET_W) << elem[i] << " ";
        cout << endl;
    }
    else
    {
        for (int i = 0; i < size; i++)
            cout << setw(SET_W) << elem[i] << endl;
    }
}

void fVector::SetSize(int size)
{
    assert(size > 0);

    if (elem)
    {
        delete [] elem;
    }
    elem = new Float [size];
    this->size = size;
}

fVector& fVector::operator= (const fVector& src)
{
    if (size != src.size)
    {
        size = src.size;
        delete [] elem;
        elem = new Float [size];
    }
    for (int i = 0; i < size; i++)
    {
        elem[i] = src.elem[i];
    }
    return *this;
}

void fVector::operator= (Float val)
{
    for (auto i = 0; i < size; i++)
    {
        elem[i] = val;
    }
}

fVector& fVector::Swap(int i, int j)
{
    if (i == j)
        return *this;

    int idx1 = i % size;
    int idx2 = j % size;

    Swap(elem[idx1], elem[idx2]);
    return *this;
}

// fVector fVector::GetBlock( int i, int j ) const
// void fVector::SetBlock( int i, int j, const fVector & );

/*-------------------------------------------------------------------------*
 *  FRIEND OPERATORS                                                       *
 *-------------------------------------------------------------------------*/
fVector operator+ (const fVector& left, const fVector& right)
{
    /* assert vector size is equal */
    assert(left.size == right.size);

    int size = left.size;
    fVector res(size);

    for (int i = 0; i < size; i++)
    {
        res.elem[i] = left.elem[i] + right.elem[i];
    }
    return res;
}

fVector operator+ (Float left, const fVector& right)
{
    int size = right.size;
    fVector res(size);

    for (int i = 0; i < size; i++)
    {
        res.elem[i] = left + right.elem[i];
    }
    return res;
}

fVector operator+ (const fVector& left, Float right)
{
    return right + left;
}

/* Binary minus */
fVector operator- (const fVector& left, const fVector& right)
{
    /* assert vector size is equal */
    assert(left.size == right.size);

    int size = left.size;
    fVector res(size);

    for (int i = 0; i < size; i++)
    {
        res.elem[i] = left.elem[i] - right.elem[i];
    }
    return res;
}

/* Unary minus */
fVector operator- (const fVector& vec)
{
    int size = vec.size;
    fVector res(size);

    for (int i = 0; i < size; i++)
        res.elem[i] = -vec.elem[i];
    return res;
}

fVector operator- (const fVector& left, Float right)
{
    int size = left.size;
    fVector res(size);

    for (int i = 0; i < size; i++)
        res.elem[i] = left.elem[i] - right;
    return res;
}

fVector operator- (Float left, const fVector& right)
{
    int size = right.size;
    fVector res(size);

    for (int i = 0; i < size; i++)
        res.elem[i] = left - right.elem[i];
    return res;
}

fVector operator* (const fVector& left, Float right)
{
    int size = left.size;
    fVector res(size);

    for (int i = 0; i < size; i++)
        res.elem[i] = left.elem[i] * right;
    return res;
}

fVector operator* (Float left, const fVector& right)
{
    int size = right.size;
    fVector res(size);

    for (int i = 0; i < size; i++)
        res.elem[i] = left * right.elem[i];
    return res;
}

fVector operator/ (const fVector& left, Float right)
{
    /* avoid division 0 */
    assert(right != 0);

    fVector res(left.size);

    for (int i = 0; i < left.size; i++)
        res.elem[i] = left.elem[i] / right;
    return res;
}

fVector operator/ (Float left, const fVector& right)
{
    fVector res(right.size);

    for (int i = 0; i < right.size; i++)
    {
        /* avoid division 0 */
        assert(right.elem[i] != 0);
        res.elem[i] = left / right.elem[i];
    }
    return res;
}

/* Element-wise division */
fVector operator/ (const fVector& left, const fVector& right)
{
    /* assert vector size is equal */
    assert(left.size == right.size);

    fVector res(left.size);
    for (int i = 0; i < left.size; i++)
    {
        /* avoid division 0 */
        assert(right.elem[i] != 0);
        res.elem[i] = left.elem[i] / right.elem[i];
    }
    return res;
}

/* Inner-product between two vectors */
Float operator* (const fVector& left, const fVector& right)
{
    /* assert vector size is equal */
    assert(left.size == right.size);

    Float res = 0;
    for (int i = 0; i < left.size; i++)
    {
        res += left.elem[i] * right.elem[i];
    }
    return res;
}

/* Cross-product between two vectors */
fVector operator^ (const fVector& left, const fVector& right)
{
    /* assert vector size is equal 3 */
    assert(left.size == 3 && right.size == 3);

    fVector res(left.size);
    for (int i = 0; i < left.size; i++)
    {
        int j = (i + 1) % left.size;
        int k = (i + 2) % left.size;
        res.elem[i] = left.elem[j] * right.elem[k] - left.elem[k] * right.elem[j];
    }
    return res;
}

fVector& operator+= (fVector& left, const fVector& right)
{
    assert(left.size == right.size);
    for (int i = 0; i < left.size; i++)
    {
        left.elem[i] = left.elem[i] + right.elem[i];
    }
    return left;
}

fVector& operator-= (fVector& left, const fVector& right)
{
    assert(left.size == right.size);
    for (int i = 0; i < left.size; i++)
    {
        left.elem[i] = left.elem[i] - right.elem[i];
    }
    return left;
}

fVector& operator*= (fVector& left, Float right)
{
    for (int i = 0; i < left.size; i++)
    {
        left.elem[i] = left.elem[i] * right;
    }
    return left;
}

fVector& operator/= (fVector& left, Float right)
{
    for (int i = 0; i < left.size; i++)
    {
        left.elem[i] = left.elem[i] / right;
    }
    return left;
}

/*-------------------------------------------------------------------------*
 *  FRIEND FUNCTIONS                                                       *
 *-------------------------------------------------------------------------*/
/* Element-wise minimum-element extraction between two vectors */
fVector Min(const fVector& a, const fVector& b)
{
    assert(a.size == b.size);
    return TwoNorm(a) > TwoNorm(b) ? b : a;
}

/* Element-wise maximum-element extraction between two vectors */
fVector Max(const fVector& a, const fVector& b)
{
    assert(a.size == b.size);
    return TwoNorm(a) > TwoNorm(b) ? a : b;
}

/* Returns two norm distance between two vectors */
Float Dist(const fVector& a, const fVector& b)
{
    assert(a.size == b.size);
    fVector res = a - b;
    return TwoNorm(res);
}

/* Normalizes a vector into an unit vector */
fVector Normalize(const fVector& src)
{
    fVector res(src.size);
    Float scalar = TwoNorm(src);
    for (int i = 0; i < src.size; i++)
        res.elem[i] = src.elem[i] / scalar;
    return res;
}

/* Returns one norm value of a vector */
Float OneNorm(const fVector& src)
{
    Float sum = 0;
    for (int i = 0; i < src.size; i++)
        sum += fabs(src.elem[i]);
    return sum;
}

/* Returns two norm value of a vector */
Float TwoNorm(const fVector& src)
{
    Float sum = 0;
    for (int i = 0; i < src.size; i++)
        sum += src.elem[i] * src.elem[i];
    return sqrt(sum);
}

/* Returns square of the two norm value of a vector */
Float TwoNormSqr(const fVector& src)
{
    return pow(TwoNorm(src), 2);
}

/* Element-wise square root of a vector */
fVector Sqrt(const fVector& src)
{
    fVector res(src.size);
    for (int i = 0; i < src.size; i++)
        res.elem[i] = sqrt(src.elem[i]);
    return res;
}

/* Mean value of a vector */
Float Mean(const fVector& src)
{
    assert(src.size > 0);
    
    Float sum = 0;
    for (int i = 0; i < src.size; i++)
        sum += src.elem[i];
    return sum / src.size;
}

/* Variance of a vector */
Float Var(const fVector& src)
{
    assert(src.size > 1);
    
    Float var = 0;
    Float u = Mean(src);
    for (int i = 0; i < src.size; i++)
    {
        var += pow(fabs(src.elem[i] - u), 2);
    }
    return var / (src.size - 1);
}

Float Var(const fVector& v1, const fVector& v2)
{
    return (v1 - Mean(v1)) * (v2 - Mean(v2)) / (v2.size - 1);
}

fVector DotMul(const fVector& v1, const fVector& v2)
{
    assert(v1.size == v2.size);
    
    fVector res(v1.size);
    for (int i = 0; i < v1.size; i++)
        res.elem[i] = v1.elem[i] * v2.elem[i];
    return res;
}

/* Standard derivation of a vector */
Float Std(const fVector& src)
{
    return sqrt(Var(src));
}

void ShowVector(const fVector& src, VecType Type /*= ColVec*/)
{
    src.Show(Type);
}

void Swap( Float& a, Float& b)
{
    Float tmp = a;
    a = b;
    b = tmp;
}
