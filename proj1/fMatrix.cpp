/*
 *	fMatrix.cpp
 *
 *	Description:
 *		Basic matrix class with some associated methods.
 *
 * 	History:
 *	 	Author			Date
 *		---------------------------
 *		youjun		 2017/03/08
 *
 */

#include "fMatrix.h"

int fMatrix::nMatCount = 0;

/*-------------------------------------------------------------------------*
 *  CONSTRUCTORS & DESTRUCTORS                                             *
 *-------------------------------------------------------------------------*/
/* Initinalize constructor */
fMatrix::fMatrix(int n_rows /* = 0 */, int n_cols /* = 0 */): rows(n_rows), cols(n_cols), elem(nullptr)
{
    if (rows > 0 && cols > 0)
    {
        elem = new Float [rows * cols] ();
        // std::memset(elem, 0, sizeof(Float) * rows * cols);
        nMatCount++;
    }
}

/* Copy constructor */
fMatrix::fMatrix(const fMatrix& src): rows(src.rows), cols(src.cols)
{
    elem = new Float [rows * cols];
    std::copy(src.elem, src.elem + rows * cols, elem);
    nMatCount++;
}

fMatrix::fMatrix(const fVector& src, VecType Type): rows(1), cols(1)
{
    if (Type == ColVec)
        rows = src.Size();
    else
        cols = src.Size();
    
    elem = new Float [rows * cols];
    Float* vecElem = src.Array();
    std::copy(vecElem, vecElem + rows * cols, elem);
    nMatCount++;
}

/* Assign constructor */
fMatrix::fMatrix(Float* Array, int n_rows, int n_cols): rows(n_rows), cols(n_cols), elem(nullptr)
{
    if (rows > 0 && cols > 0)
    {
        elem = new Float [rows * cols];
        std::copy(Array, Array + rows * cols, elem);
        nMatCount++;
    }
}

fMatrix::fMatrix(int n_rows, int n_cols, Float* Array): rows(n_rows), cols(n_cols), elem(nullptr)
{
    if (rows > 0 && cols > 0)
    {
        elem = new Float [rows * cols];
        std::copy(Array, Array + rows * cols, elem);
        nMatCount++;
    }
}

/* Destructor */
fMatrix::~fMatrix()
{
    if (elem)
    {
        delete [] elem;
        elem = nullptr;
        nMatCount--;
        
#ifdef _DEBUG_CNT_
        std::cout << "nMatCount: " << nMatCount << std::endl;
#endif
    }
}

/*-------------------------------------------------------------------------*
 *  PUBLIC FUNCTIONS                                                       *
 *-------------------------------------------------------------------------*/

void fMatrix::Show() const
{
    using namespace std;
    if (rows == 0 && cols == 0)
    {
        cout << "None" << endl;
        return;
    }

    cout << fixed << setprecision(SET_P);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << setw(SET_W) << elem[i * cols + j] << " ";
        cout << endl;
    }
}

fMatrix& fMatrix::operator= (const fMatrix& M)
{
    if (M.rows != rows || M.cols != cols)
    {
        rows = M.rows;
        cols = M.cols;
        delete [] elem;
        elem = new Float [rows * cols];
    }
    std::copy(M.elem, M.elem + rows * cols, elem);
    return *this;
}

fMatrix& fMatrix::operator= (Float s)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            elem[i * cols +j] = s;
    return *this;
}

/*-------------------------------------------------------------------------*
 *  FRIEND OPERATORS                                                       *
 *-------------------------------------------------------------------------*/
// 1. A+B
fMatrix operator+ (const fMatrix& left, const fMatrix& right)
{
    assert(left.rows == right.rows && left.cols == right.cols);
    
    fMatrix res(left.rows, left.cols);
    for (int i = 0; i < left.rows; i++)
        for (int j = 0; j < left.cols; j++)
        {
            int index = i * res.cols + j;
            res.elem[index] = left.elem[index] + right.elem[index];
        }
    return res;
}

// -Matrix
fMatrix operator- (const fMatrix& src)
{
    fMatrix res(src.rows, src.cols);
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            int index = i * res.cols + j;
            res.elem[index] = -src.elem[index];
        }
    return res;
}

// 2. A-B
fMatrix operator- (const fMatrix& left, const fMatrix& right)
{
    assert(left.rows == right.rows && left.cols == right.cols);
    
    fMatrix res(left.rows, left.cols);
    for (int i = 0; i < left.rows; i++)
        for (int j = 0; j < left.cols; j++)
        {
            int index = i * res.cols + j;
            res.elem[index] = left.elem[index] - right.elem[index];
        }
    return res;
}

// 3. c*A or A*c
fMatrix operator* (const fMatrix& src, Float val)
{
    fMatrix res(src.rows, src.cols);
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            int index = i * res.cols + j;
            res.elem[index] = src.elem[index] * val;
        }
    return res;
}

fMatrix operator* (Float val,  const fMatrix& src)
{
    fMatrix res(src.rows, src.cols);
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            int index = i * res.cols + j;
            res.elem[index] = src.elem[index] * val;
        }
    return res;
}

// 4. A/c
fMatrix operator/ (const fMatrix& src, Float val)
{
    fMatrix res(src.rows, src.cols);
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            int index = i * res.cols + j;
            res.elem[index] = src.elem[index] / val;
        }
    return res;
}

// c/A
fMatrix operator/ (Float val, const fMatrix& src)
{
    fMatrix res(src.rows, src.cols);
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            int index = i * res.cols + j;
            res.elem[index] = val / src.elem[index];
        }
    return res;
}
// 5. A*B
fMatrix operator* (const fMatrix& left, const fMatrix& right)
{
    assert(left.cols == right.rows);
    
    fMatrix res(left.rows, right.cols);
    for (int i = 0; i < left.rows; i++)
        for (int j = 0; j < right.cols; j++)
        {
            Float sum = 0;
            // k is left.cols and right.rows
            for (int k = 0; k < left.cols; k++)
                sum += left.elem[i * left.cols + k] * right.elem[k * right.cols + j];
            res.elem[i * res.cols + j] = sum;
        }
    return res;
}

fVector operator* (const fMatrix& mat, const fVector& vec)
{
    // std::cout << "here: " << mat.cols <<" "<< std::endl;
    assert(mat.cols == vec.Size());
    
    fMatrix vecMat(vec);
    Float* elem = (mat * vecMat).elem;
    return fVector(elem, mat.rows);
}

fVector operator* (const fVector& vec, const fMatrix& mat)
{
    assert(vec.Size() == mat.rows);
    
    fMatrix vecMat(vec, RowVec);
    Float* elem = (vecMat * mat).elem;
    return fVector(elem, mat.cols);
}

fMatrix& operator+= (fMatrix& left, const fMatrix& right)
{
    assert(left.rows == right.rows && left.cols == right.cols);
    
    for (int i = 0; i < left.rows; i++)
        for (int j = 0; j < left.cols; j++)
        {
            int index = i * left.cols + j;
            left.elem[index] += right.elem[index];
        }
    return left;
}

fMatrix& operator-= (fMatrix& left, const fMatrix& right)
{
    assert(left.rows == right.rows && left.cols == right.cols);
    
    for (int i = 0; i < left.rows; i++)
        for (int j = 0; j < left.cols; j++)
        {
            int index = i * left.cols + j;
            left.elem[index] -= right.elem[index];
        }
    return left;
}

fMatrix& operator*= (fMatrix& src, Float val)
{
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            src.elem[i * src.cols + j] *= val;
        }
    return src;
}

fMatrix& operator*= (fMatrix& left, const fMatrix& right)
{
    assert(left.cols == right.rows);
    
    left = left * right;
    return left;
}

fVector& operator*= (fVector& vec, const fMatrix& mat)
{
    assert(vec.Size() == mat.rows);
    
    fMatrix vecMat(vec, RowVec);
    Float* elem = (vecMat * mat).elem;
    vec = fVector(elem, vecMat.cols);
    return vec;
}

fMatrix& operator/= (fMatrix& src, Float val)
{
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            src.elem[i * src.cols + j] /= val;
        }
    return src;
}

/*-------------------------------------------------------------------------*
 *  FRIEND FUNCTIONS                                                       *
 *-------------------------------------------------------------------------*/
// Transpose of a matrix
fMatrix Transp(const fMatrix& src)
{
    fMatrix res(src.cols, src.rows);
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
            res.elem[j * res.cols + i] = src.elem[i * src.cols + j];
    return res;
}

// Computes A * Transp(A)
fMatrix AATransp(const fMatrix& src)
{
    return src * Transp(src);
}

// Computes Transp(A) * A
fMatrix ATranspA(const fMatrix& src)
{
    return Transp(src) * src;
}

// Computes the outer product of two vectors
fMatrix Outer(const fVector& left, const fVector& right)
{
    fMatrix res(left.Size(), right.Size());
    for (int i = 0; i < res.rows; i++)
        for (int j = 0; j < res.cols; j++)
            res.elem[i * res.cols + j] = left(i) * right(j);
    return res;
}

// Returns an nSizexnSize identity matrix
fMatrix Identity(int nSize)
{
    assert(nSize > 0);
    
    fMatrix res(nSize, nSize);
    for (int i = 0; i < nSize; i++)
        res.elem[i * res.cols + i] = 1;
    return res;
}

// Returns the square matrix with the elements of the vector d along its diagonal
fMatrix Diag(const fVector& src)
{
    int size = src.Size();
    fMatrix res(size, size);
    for (int i = 0; i < size; i++)
        res.elem[i * res.cols + i] = src(i);
    return res;
}

// Returns the vector consisting of the diagonal elements of the matrix M
fVector Diag(const fMatrix& src)
{
    assert(src.rows == src.cols);
    
    fVector res(src.rows);
    for (int i = 0; i < src.rows; i++)
        res(i) = src.elem[i * src.cols + i];
    return res;
}

// Returns the 3 x 3 diagonal matrix with x, y, and z as its diagonal elements
fMatrix Diag(Float x, Float y, Float z)
{
    return Diag(fVector(x, y, z));
}

// Computes the determinant of a square matrix
double Determinant(const fMatrix& src)
{
    // check is square
    assert(src.rows == src.cols);

    // only one element
    if (src.rows == 1)
        return src.elem[0];

    Float det = 0;
    // control col's pos
    for (int i = 0; i < src.cols; i++)
    {
        // coefficient
        Float coff = i % 2 == 0 ? 1 : -1;
        det += coff *
               src.elem[i] *
               Determinant(src.GetBlock(1, i+1, src.rows-1, src.cols-1));
    }
    return det;
}

// Computes the trace of a square matrix
double Trace(const fMatrix& src)
{
    assert(src.rows == src.cols);
    
    Float sum = 0;
    for (int i = 0; i < src.rows; i++)
        sum += src.elem[i * src.cols +i];
    return sum;
}

// Computes the L1-norm of the matrix A, which is the maximum absolute column sum
double OneNorm(const fMatrix& src)
{
    Float max = 0;
    for (int i = 0; i < src.cols; i++)
    {
        Float sum = OneNorm(src.GetCol(i));
        max = sum > max ? sum : max;
    }
    return max;
}

// Computes the Inf-norm of the matrix A, which is the maximum absolute row sum
double InfNorm(const fMatrix& src)
{
    Float max = 0;
    for (int i = 0; i < src.rows; i++)
    {
        Float sum = OneNorm(src.GetRow(i));
        max = sum > max ? sum : max;
    }
    return max;
}

fMatrix Cofactor(const fMatrix& src)
{
    assert(src.rows == src.cols);

    fMatrix res(src.rows, src.cols);
    /* control index of elem */
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            Float det = Determinant(src.GetBlock(i+1, j+1, src.rows-1, src.cols-1));

            int idx = i * res.cols + j;
            if (src.rows == 2)
                res.elem[idx] = idx % 3 == 0 ? det : -det;
            else if (src.rows >= 3)
                res.elem[idx] = idx % 2 == 0 ? det : -det;
        }
    return res;
}

// Computes the inverse of a square matrix
fMatrix Inverse(const fMatrix& src)
{
    assert(src.rows == src.cols);
    fMatrix res(src);
    return res.Inv();
}

// Computes Cholesky decomposition of a square matrix
fMatrix Cholesky(const fMatrix& src, int lower)
{
    assert(src.rows == src.cols);
    
    for (int i = 0; i < src.rows; i++)
        assert(src.elem[i * src.cols + i] > 0);
    
    fMatrix res(src.rows, src.cols);
    for (int i = 0; i < src.rows; i++)
    {
        Float sum = 0;
        /* find Gii of trace elem */
        int gii = i * res.cols + i;
        for (int j = 0; j < i; j++)
            sum += pow(res.elem[i * res.cols + j], 2);
        res.elem[gii] = sqrt(src.elem[gii] - sum);
        
        /* find Gij of col elem */
        for (int j = i + 1; j < res.rows; j++)
        {
            sum = 0;
            int gij = j * res.cols + i;
            for (int k = 0; k < i; k++)
                sum += res.elem[j * res.cols + k] * res.elem[i * res.cols + k];
            res.elem[gij] = (src.elem[gij] - sum) / res.elem[gii];
        }
    }
    return lower ? res : Transp(res);
}

// Computes column mean value of a matrix
fVector Mean(const fMatrix& src, VecType type)
{
    int size = type == ColVec ? src.cols : src.rows;
    
    fVector res(size);
    for (int i = 0; i < size; i++)
    {
        res(i) = type == ColVec ?
            OneNorm(src.GetCol(i)) / size:
            OneNorm(src.GetRow(i)) / size;
    }
    return res;
}

// Ref: http://soybeanmilkmania.blogspot.tw/2012/08/variance-covariance-matrix.html
// Returns a covariance matrix of a square matrix
fMatrix Cov(const fMatrix& src)
{
    assert(src.rows == src.cols);
    
    fMatrix res(src.rows, src.rows);
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
            res.elem[i * res.cols + j] = Var(src.GetCol(i), src.GetCol(j));

    return res;
}

// Returns a covariance matrix of a vector, using outer product
fMatrix Cov(const fVector& src)
{
    fVector subMean = src - Mean(src);
    return Outer(subMean, subMean) / (src.Size() - 1);
}

/*-------------------------------------------------------------------------*
 *  MATRIX OPERATION FUNCTIONS                                             *
 *-------------------------------------------------------------------------*/
// 7. Swap
fMatrix& fMatrix::SwapRows(int i1, int i2)
{
    if (i1 == i2)
        return *this;

    int idx1 = i1 % rows;
    int idx2 = i2 % rows;

    for (int i = 0; i < cols; i++)
    {
        Swap(elem[idx1 * cols + i], elem[idx2 * cols + i]);
    }
    return *this;
}

fMatrix& fMatrix::SwapCols(int j1, int j2)
{
    if (j1 == j2)
        return *this;

    int idx1 = j1 % cols;
    int idx2 = j2 % cols;

    for (int i = 0; i < rows; i++)
    {
        Swap(elem[i * cols + idx1], elem[i * cols + idx2]);
    }
    return *this;
}

// 8. Inverse
fMatrix& fMatrix::Inv()
{
    assert(rows == cols);
    fMatrix eyes = Identity(rows);

    /* Gauss-Jordan */
    // control diagonal element
    for (int i = 0; i < rows; i++)
    {
        // elem equal 0
        if (elem[i * cols + i] == 0)
        {
            for (int j = i+1; j < rows; j++)
            {
                // elem is not 0 that below row of i 
                if (elem[j * cols + i] != 0)
                {
                    // swap rows
                    SwapRows(i, j);
                    eyes.SwapRows(i, j);
                    break;
                }
            }
        }

        // assert is there inverse matrix
        assert(elem[i * cols + i] != 0);

        // let diagonal element is 1, and divide elem of row
        Float diag_elem = elem[i * cols + i];
        for (int j = 0; j < cols; j++)
        {
            if (j >= i)
                elem[i * cols + j] /= diag_elem;
            eyes.elem[i * cols + j] /= diag_elem;
        }

        // 消去時, 所有的row都消去
        for (int j = 0; j < rows; j++)
        {
            // other element in the same column
            Float other_elem = elem[j * cols + i];
            // 該行元素除了對角線元素, 其他減到0
            if (i != j && other_elem != 0)
            {
                for (int k = 0; k < cols; k++)
                {
                    if (k >= i)
                        elem[j * cols + k] -= elem[i * cols + k] * other_elem;
                    eyes.elem[j * cols + k] -= eyes.elem[i * cols + k] * other_elem;
                }
            }
        }
    }
    return *this = eyes;
}

fVector fMatrix::GetCol(int col) const
{
    assert(col < cols);

    Float* vecElem = GetBlock(0, col, rows, 1).elem;
    return fVector(vecElem, rows);
}

fVector fMatrix::GetRow(int row) const
{
    assert(row < rows);
    
    Float* vecElem = GetBlock(row, 0, 1, cols).elem;
    return fVector(vecElem, cols);
}

fMatrix fMatrix::GetBlock(int row_start, int col_start, int row_size, int col_size) const
{
    assert(row_start >= 0 && col_start >= 0 && row_size > 0 && col_size > 0);
    
    fMatrix res(row_size, col_size);
    /* get index of elem of original matrix for user desired */
    for (int i = 0; i < row_size; i++)
        for (int j = 0; j < col_size; j++)
        {
            int idx = ((i + row_start) % rows) * cols + (j + col_start) % cols;
            res.elem[i * res.cols + j] = idx;
        }
    
    /* sort index */
    int size = res.rows * res.cols;
    std::sort(res.elem, res.elem + size);
    /* get elem from original matrix */
    for (int i = 0; i < size; i++)
    {
        res.elem[i] = elem[(int) res.elem[i]];
    }
    return res;
}

void fMatrix::SetBlock(int row_start, int col_start, int row_size, int col_size, const fVector& src)
{
    assert(row_start >= 0 && col_start >= 0 && row_size > 0 && col_size > 0);
    
    /* get index of elem of original matrix for user desired */
    for (int i = 0; i < row_size; i++)
        for (int j = 0; j < col_size; j++)
        {
            int idx = ((i + row_start) % rows) * cols + (j + col_start) % cols;
            elem[idx] = src(i + j);
        }
}
























