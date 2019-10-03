#include "matrix.h"
#include "../simtypes.h"
#include "../exception.h"

#define DATA_AT(x,y,c) ((x)*(c)+(y)) 

/** 
 * create a new matrix
 *
 * input :
 * Param 1 (rows) : Number Of Matrix Rows
 * Param 2 (cols) : Number Of Matrix Cols
 * Param 3 (data) : Matrix Data Pointer
 * 
 * output:  a new Matrix 
 */
Matrix createMatrix(const int rows,const int cols,float* data)
{
	Matrix mat;
	mat.rows = rows;
	mat.cols = cols;
	mat.data = data;
	return mat;
}

/** 
 * matrix A add matrix B
 *
 * input :
 * Param 1 (result) : Result Matrix Pointer
 * Param 2 (A)      : A Matrix Pointer
 * Param 3 (B)      : B Matrix Pointer
 * 
 * output:  Status Code
 * Error: ERROR_CODE 1
 * SUCCESS: SUCCESS    0 
 */
DETECTION int add(Matrix *result,const Matrix* A,const Matrix* B)
{
	//Detecting srouce matrix
	if(!( A && B ) || !(A->data && B->data)) {
		return ERROR(
		"Null Pointer Exception",
		"Matrix A or B is NULL",
		ERROR_RET(NULL_POINTER));
	}
	//Detecting matrix format
	if(!((A->rows) == (B->rows) &&
   	((A->cols) == (B->cols)) && 
	((A->cols)&&(A->rows)))){
		return ERROR(
		"Matrix Operation Exception",
		"matrix format inconsistency",
		ERROR_CODE
		);
	}
	//Compute
	__add(result,A,B);
	return SUCCESS;
}

FAST void __add(Matrix *result,const Matrix* A,const Matrix* B)
{
	result->rows = A->rows;
	result->cols = A->cols;
	int size = (A->rows)*(A->cols);
	float data[size];
	int index;
	for(index = 0 ; index < size; index++){
		result->data[index] = (A->data[index]) + (B->data[index]);
	}
}
/** 
 * matrix A times k
 *
 * input :
 * Param 1 (result) : Result Matrix Pointer
 * Param 2 (A)      : A Matrix Pointer
 * Param 3 (k)      : Number k
 * 
 * output:  Status Code
 * Error: ERROR_CODE 1
 * SUCCESS: SUCCESS    0 
 */
DETECTION int mulConst(Matrix *result,const Matrix* A,const float k)
{
	//Detecting srouce matrix
	if(!A || !(A->data)) {
		return ERROR(
		"Null Pointer Exception",
		"Matrix A is NULL",
		ERROR_RET(NULL_POINTER));
	}
	//Detecting Matrix format
	if(!((A->cols)&&(A->rows))){
		return ERROR(
		"Matrix Operation Exception",
		"matrix format inconsistency",
		ERROR_CODE
		);
	}
	//Compute
	__mulConst(result,A,k);
	return SUCCESS;
}

FAST void __mulConst(Matrix *result,const Matrix* A,const float k)
{
	result->rows = A->rows;
	result->cols = A->cols;
	int size = (A->rows)*(A->cols);
	int index;
	for(index = 0 ; index < size; index++){
		result->data[index] = (A->data[index])*k;
	}	
}

/** 
 * matrix A mul matrix B
 *
 * input :
 * Param 1 (result) : Result Matrix Pointer
 * Param 2 (A)      : A Matrix Pointer
 * Param 3 (B)      : B Matrix Pointer
 * 
 * output:  Status Code
 * Error: ERROR_CODE 1
 * SUCCESS: SUCCESS    0 
 */
DETECTION int mul(Matrix *result, const Matrix* A, const Matrix* B)
{
	//Detecting srouce matrix
	if(!( A && B ) || !(A->data && B->data)) {
		return ERROR(
		"Null Pointer Exception",
		"Matrix A or B is NULL",
		ERROR_RET(NULL_POINTER));
	}
	//Detecting Matrix format
	if(!(A->cols == B->rows &&
		(A->cols)&&(B->cols)&&
		(A->rows)&&(B->rows))){
		return ERROR(
		"Matrix Operation Exception",
		"matrix format inconsistency",
		ERROR_CODE
		);
	}
	//Compute
	__mul(result,A,B);
	return SUCCESS;
}

FAST void __mul(Matrix *result, const Matrix* A, const Matrix* B)
{
	int rows = A->rows;
	int cols = B->cols;
	int inner = A->cols;
	
	result->rows = rows;
	result->cols = cols;
	
	float *data = result->data;
	float *Adata = A->data;
	float *Bdata = B->data;

	int i,j,k;
	float sum;
	for ( i = 0 ; i < rows; i++){
		for(j = 0 ; j < cols ; j++){
			sum = 0;
			for (k = 0; k < inner ; k++) {
				sum += 
					Adata[DATA_AT(i,k,A->cols)]*
					Bdata[DATA_AT(k,j,B->cols)];
			}
			data[DATA_AT(i,j,cols)] = sum; 
		}
	}
	
}
/* 
 * clone Matrix
 * input:
 * Param 1 (dist) : Destination Matrix Pointer 
 * Param 2 (src)  : Source Matrix Pointer
 *
 * output:  Status Code
 * Error: ERROR_CODE 1
 * SUCCESS: SUCCESS    0 
 */
DETECTION int cloneMatrix(Matrix* dist,const Matrix* src)
{
	//Detecting srouce matrix
	if( !src || !(src->data)) {
		return ERROR(
		"Null Pointer Exception",
		"Matrix src is NULL",
		ERROR_RET(NULL_POINTER));
	}
	//Clone
	if(dist != src){
		__cloneMatrix(dist,src);
		return SUCCESS;
	}
	return ERROR(
		"Matrix Operation Exception",
		"The source and destination of CLONE cannot be the same",
		ERROR_CODE
		);
}

FAST void __cloneMatrix(Matrix* dist,const Matrix* src)
{
	dist->rows = src->rows;
	dist->cols = src->cols;
	int i,size = (src->rows)*(src->cols);
	for(i = 0;i < size ; i++){
		dist->data[i] = src->data[i];
	}
}

/* 
 * transpose Matrix
 * input:
 * Param 1 (dist) : Destination Matrix Pointer 
 * Param 2 (src)  : Source Matrix Pointer
 *
 * output:  Status Code
 * Error: ERROR_CODE 1
 * SUCCESS: SUCCESS    0 
 */
DETECTION int transpose(Matrix* dist,const Matrix* src)
{
	//Detecting srouce matrix
	if( !src || !(src->data)) {
		return ERROR(
		"Null Pointer Exception",
		"Matrix src is NULL",
		ERROR_RET(NULL_POINTER));
	}
	//Transpose
	if(dist != src){
		__transpose(dist,src);
		return SUCCESS;
	}
	return ERROR(
		"Matrix Operation Exception",
		"The source and destination of TRANSPOSE cannot be the same",
		ERROR_CODE
		);
}

FAST void __transpose(Matrix* dist,const Matrix* src)
{
	dist->rows = src->cols;
	dist->cols = src->rows;
	int i,j;
	for ( i = 0 ; i < src->rows; i++){
		for( j = 0 ; j < src->cols ; j++){
			dist->data[DATA_AT(j,i,dist->cols)] = 
			src->data[DATA_AT(i,j,src->cols)]; 
		}
	}
}

/*
 * calculate the value of determinant 
 * input:
 * Param 1 (result) : float result Pointer 
 * Param 2 (mat)    : Source Matrix Pointer
 * 
 * output:Status Code
 * Error: ERROR_CODE 1
 * SUCCESS: SUCCESS    0 
 */
DETECTION int det(float* result,const Matrix* mat)
{
	//Detecting srouce matrix
	if( !mat || !(mat->data)) {
		return ERROR(
		"Null Pointer Exception",
		"Matrix src is NULL",
		ERROR_RET(NULL_POINTER));
	}
	//Detecting Matrix format
	if(mat->cols != mat->rows){
		return ERROR(
		"Matrix operation Exception",
		"matrix format inconsistency",
		ERROR_CODE
		);
	}
	*result = __det(mat);
	return SUCCESS;
}

PRIVATE void permutation(float* result,const Matrix* mat,int* order,int now);
PRIVATE int inversionNumber(const int* order,int size);
PRIVATE static __inline__ float det2X2(const Matrix* mat);
PRIVATE static __inline__ float det3X3(const Matrix* mat);

FAST float __det(const Matrix* mat)
{
	int size = mat->rows;
	switch(size){
	case 1: return mat->data[0];
	case 2: return det2X2(mat);
	case 3: return det3X3(mat);
	}
	
	//create a default order array buffer
	int orderBuffer[size];
	int i;
	for(i = 0 ; i < size ; i ++){
		orderBuffer[i] = i;
	}
	float result = 0;
	permutation(&result,mat,orderBuffer,0);
	return result;
}

PRIVATE void permutation(float* result,const Matrix* mat,int* order,int now)
{
	int i;
    if(now != mat->cols){
		for(i = now; i < mat->cols ; i++)
		{
			SWAP(order[now],order[i]);
			permutation(result,mat,order,now+1);
			SWAP(order[now],order[i]);
		}
	} else {
		float num = 1;
		int in = inversionNumber(order,mat->cols);
		for(i = 0;i < mat->rows;i++){
			num *= mat->data[DATA_AT(i,order[i],mat->cols)];
		}
		*result += in&1?-num:num;
	}
} FUNCTION_USED_BY(__det,"Find all combinations of different rows and columns");

PRIVATE int inversionNumber(const int* order,int size)
{
	int i,j;
	int ret = 0;
	for(i = 0; i < size ; i++){
		for(j = 0; j < i; j++){
			if(order[i] < order[j]){
				ret ++;
			}
		}
	}
	return ret;
} FUNCTION_USED_BY(permutation,"Calculate the inverse number of a given order");

PRIVATE static __inline__ float det2X2(const Matrix* mat)
{
	return (mat->data[0])*(mat->data[3]) - (mat->data[1])*(mat->data[2]);
}

PRIVATE static __inline__ float det3X3(const Matrix* mat)
{
	float* data = mat->data;
	return
	  data[0]*data[4]*data[8] + data[1]*data[5]*data[6] + data[2]*data[3]*data[7] 
	- data[0]*data[5]*data[7] - data[1]*data[3]*data[8] - data[2]*data[4]*data[6];
}

/* 
 * inverse Matrix
 * input:
 * Param 1 (dist) : Destination Matrix Pointer 
 * Param 2 (src)  : Source Matrix Pointer
 *
 * output:
 * IRREVERSIBLE : Matrix irreversibility  
 * Error: ERROR_CODE 1
 * SUCCESS: SUCCESS    0 
 */

DETECTION int inverse(Matrix* dist,const Matrix* src)
{
	//Detecting srouce matrix
	if( !src || !(src->data)) {
		return ERROR(
		"Null Pointer Exception",
		"Matrix src is NULL",
		ERROR_RET(NULL_POINTER));
	}
	//inverse
	if(dist != src){
		return __inverse(dist,src);
	}
	return ERROR(
		"Matrix Operation Exception",
		"The source and destination of INVERSE cannot be the same",
		ERROR_CODE
		);
}

PRIVATE void LUDecomposition(Matrix* dist,const Matrix* mat);
PRIVATE float innerSumLrkUki(const float* L,const float* U,const int size, int r, int i);
PRIVATE float innerSumLikUkr(const float* L,const float* U,const int size, int r, int i);
PRIVATE void inversionOfLowerTriangularMatrix(Matrix* dist,const Matrix* src,const int rowStart,const int rowEnd,const int colStart,const int colEnd);
PRIVATE static __inline__ void inverse1X1(Matrix* dist,const Matrix* src);
PRIVATE static __inline__ void inverse2X2(Matrix* dist,const Matrix* src);

FAST int __inverse(Matrix* dist,const Matrix* src)
{
	float detSrc = __det(src);
	if(detSrc == 0){
		return IRREVERSIBLE;
	}
	
	switch(src->rows){
	case 1: inverse1X1(dist,src);return SUCCESS;
	case 2: inverse2X2(dist,src);return SUCCESS;
	}
	
	LUDecomposition(dist,src);
	return SUCCESS;
}

PRIVATE void LUDecomposition(Matrix* dist,const Matrix* src)
{
	int size = src->rows;
	int matrixSize = size*size;
	float* data = src->data;
	float L[matrixSize],U[matrixSize];
	////start
	/*FRIST:
	 *L frist col and U frist row
	 *U1i=A1i,Li1=Ai1/U11
	 */
	int r,i;
	for (i = 0; i < size; i++) {
    	U[DATA_AT(0,i,size)]= data[DATA_AT(0,i,size)];
        L[DATA_AT(i,0,size)]= data[DATA_AT(i,0,size)]/U[DATA_AT(0,0,size)];
    }
	//compute U r row£¬L r col
    //uri=ari-¦²(k=1->r-1)lrkuki    (i=r,r+1,...,n)
    //lir=air-¦²(k=1->r-1)likukr    (i=r+1,r+2,...,n&&r¡Ùn)
    for (r = 1; r < size; r++) {
        for (i = r; i < size; i++) {
            U[DATA_AT(r,i,size)] = data[DATA_AT(r,i,size)] - innerSumLrkUki(L,U,size,r,i);
            if(i==r) L[DATA_AT(r,r,size)] = 1;
            else if(r==size) L[DATA_AT(size,size,size)] = 1;
            else {
            	L[DATA_AT(i,r,size)] = 
				(data[DATA_AT(i,r,size)] - innerSumLikUkr(L,U,size,r,i))/U[DATA_AT(r,r,size)];
            }
        }
    }
	////end
	Matrix matrixL = createMatrix(size,size,L);
	Matrix matrixU = createMatrix(size,size,U);
	
	float iL[matrixSize],iU[matrixSize],tmpData[matrixSize];
	Matrix iMatrixL = createMatrix(size,size,iL);
	Matrix iMatrixU = createMatrix(size,size,iU);
	Matrix tmpMatrix = createMatrix(size,size,tmpData);
	
	//get L' and U'
	inversionOfLowerTriangularMatrix(&iMatrixL,&matrixL,0,size,0,size);
	__transpose(&tmpMatrix,&matrixU);
	inversionOfLowerTriangularMatrix(&matrixU,&tmpMatrix,0,size,0,size);
	__transpose(&iMatrixU,&matrixU);
	
	//A' = U'L'
	__mul(dist,&iMatrixU,&iMatrixL);
	
	
} FUNCTION_USED_BY(__inverse,"LU Decomposition of Matrix");

PRIVATE float innerSumLrkUki(const float* L,const float* U,const int size, int r, int i) 
{
    float sum = 0;
    int k;
    for (k = 0; k < r; k++) {
        sum += 
		L[DATA_AT(r,k,size)] * U[DATA_AT(k,i,size)];
    }
    return sum;
}

PRIVATE float innerSumLikUkr(const float* L,const float* U,const int size, int r, int i)
{
	float sum = 0;
    int k;
    for (k = 0; k < r; k++) {
        sum += 
		L[DATA_AT(i,k,size)] * U[DATA_AT(k,r,size)];
    }
    return sum;
}

PRIVATE void inversionOfLowerTriangularMatrix(
	Matrix* dist,
	const Matrix* src,
	const int rowStart,
	const int rowEnd,
	const int colStart,
	const int colEnd
	)
{
	int size = rowEnd-rowStart;
	switch(size){
	    case 1: 
		dist->data[0] = 1.0f/src->data[DATA_AT(rowStart,colStart,src->cols)];
		return;
	    case 2: 
		{
		    float a,b,c,d;
		    a = src->data[DATA_AT(rowStart  ,colStart  ,src->cols)];
		    b = src->data[DATA_AT(rowStart  ,colStart+1,src->cols)];
		    c = src->data[DATA_AT(rowStart+1,colStart  ,src->cols)];
		    d = src->data[DATA_AT(rowStart+1,colStart+1,src->cols)];
		    float n = 1.0f/(a*d - c*b);
			dist->data[0] =  d*n;
			dist->data[1] = -b*n;
			dist->data[2] = -c*n;
			dist->data[3] =  a*n;
	    }
	    
		return;
	}
	
	int Asize = size/2;
	int Bsize = size - Asize;
	
	float iAData[Asize*Asize],iBData[Bsize*Bsize],CData[Asize*Bsize];
	Matrix iA = createMatrix(Asize,Asize,iAData);
	Matrix iB = createMatrix(Bsize,Bsize,iBData);
	Matrix C = createMatrix(Bsize,Asize,CData);
	
	inversionOfLowerTriangularMatrix(&iA,src,rowStart,rowStart + Asize,colStart,colStart + Asize);
	inversionOfLowerTriangularMatrix(
	&iB,src,
	rowStart + Asize,
	rowStart + Asize + Bsize,
	colStart + Asize,
	colStart + Asize + Bsize);
	__submatrix(&C,src,rowStart + Asize,rowEnd,colStart,colStart + Asize);
	
	float t0Data[Asize*Bsize],t1Data[Asize*Bsize];
	Matrix tmp0 = createMatrix(Bsize,Asize,t0Data);
	Matrix tmp1 = createMatrix(Bsize,Asize,t1Data);
	
	__mul(&tmp0,&iB,&C);
	__mul(&tmp1,&tmp0,&iA);
	__mulConst(&tmp0,&tmp1,-1);
	
	float *data = dist->data;
	int i,j;
	int all = size*size ;
	for(i = 0; i < all ;i++){
		data[i] = 0;
	}
	
	for(i = 0; i < Asize; i++ ){
		for(j = 0 ; j < Asize ; j++){
			data[DATA_AT(i,j,size)] = 
			iA.data[DATA_AT(i,j,Asize)];
		}
	}
	for(i = 0; i < Bsize ; i++){
		for(j = 0 ; j < Bsize ; j++){
		    data[DATA_AT(Asize + i,Asize + j,size)] = 
			iB.data[DATA_AT(i,j,Bsize)];
		}
	}
	for(i = 0; i < Bsize ; i++){
		for(j = 0 ; j < Asize ; j++){
		    data[DATA_AT(Asize + i,j,size)] = 
			tmp0.data[DATA_AT(i,j,Asize)];
		}
	}
}

PRIVATE static __inline__ void inverse1X1(Matrix* dist,const Matrix* src)
{
	dist->rows = 1;
	dist->cols = 1;
	dist->data[0] = 1.0f/(src->data[0]);
}

PRIVATE static __inline__ void inverse2X2(Matrix* dist,const Matrix* src)
{
	dist->rows = 2;
	dist->cols = 2;
	float n = 1.0f/det2X2(src);
	float* data = dist->data;
	data[0] =  src->data[3]*n; 
	data[1] = -src->data[1]*n;
	data[2] = -src->data[2]*n;
	data[3] =  src->data[0]*n;
}

/*
 * get Submatrix (form rowStart,colStart to rowEnd,colEnd)
 * input:
 * Param 1 (dist)     : Destination Matrix Pointer 
 * Param 2 (src)      : Source Matrix Pointer
 * Param 3 (rowStart) : Which row to start with
 * Param 4 (rowEnd)   : Which row ends
 * Param 5 (colStart) : Which column to start with 
 * Param 6 (colEnd)   : Which column ends
 *
 * output:  Status Code
 * Error: ERROR_CODE 1
 * SUCCESS: SUCCESS    0 
 */
DETECTION int submatrix(
	Matrix* dist,
    const Matrix* src,
	int rowStart,
	int rowEnd,
	int colStart,
	int colEnd
    )
{
    //Detecting srouce matrix
	if( !src || !(src->data)) {
		return ERROR(
		"Null Pointer Exception",
		"Matrix src is NULL",
		ERROR_RET(NULL_POINTER));
	}
	
	//Detecting Matrix Parameter
	if(rowStart && rowEnd && colStart && colEnd &&
	   rowEnd > rowStart && colEnd > colStart &&
	   src->rows > rowEnd && src->cols > colEnd 
	){
		return ERROR(
		"Matrix Parameter Exception",
		"matrix parameter data error",
		ERROR_CODE
		);
	}
	
	if(dist != src){
		__submatrix(dist,src,rowStart,rowEnd,colStart,colEnd);
		return SUCCESS;
	}
	
	return ERROR(
		"Matrix Operation Exception",
		"The source and destination of SUBMATRIX cannot be the same",
		ERROR_CODE
		);
}

FAST void __submatrix(
	Matrix* dist,
    const Matrix* src,
	int rowStart,
	int rowEnd,
	int colStart,
	int colEnd
	)
{
	int rows = rowEnd - rowStart;
	int cols = colEnd - colStart;
	dist->rows = rows;
	dist->cols = cols;
	int i,j;
	for(i = rowStart ; i < rowEnd ;i++){
		for(j = colStart; j < colEnd ; j++){
			dist->data[DATA_AT(i - rowStart ,j - colStart ,dist->cols)] =
			src->data[DATA_AT(i,j,src->cols)];
		}
	}
}

float matrixGet(const Matrix* mat,const int row,const int col)
{
	return mat->data[DATA_AT(row,col,mat->cols)];
}

void matrixSet(Matrix* mat,const int row,const int col,const float num)
{
	mat->data[DATA_AT(row,col,mat->cols)] = num;
}

#undef DATA_AT

