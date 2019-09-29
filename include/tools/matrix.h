#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "../simtypes.h"

#define SWAP(A,B) do{typeof(A) C=A;A=B;B=C;}while(0)

#ifndef __MATRIX__
#define __MATRIX__
struct Matrix{
	int rows;
	int cols;
	float* data;
};
typedef struct Matrix Matrix;
#endif

#define SUCCESS     0
#define ERROR_CODE  1
#define IRREVERSIBLE 0x000c
 
extern Matrix createMatrix(const int rows,const int cols,float* data);
extern void __add(Matrix *result,const Matrix* A,const Matrix* B);
extern int add(Matrix *result,const Matrix* A,const Matrix* B);
extern void __mulConst(Matrix *result,const Matrix* A,const float k);
extern int mulConst(Matrix *result,const Matrix* A,const float k);
extern void __mul(Matrix *result, const Matrix* A, const Matrix* B);
extern int mul(Matrix *result,const Matrix* A,const Matrix* B);
extern void __cloneMatrix(Matrix* dist,const Matrix* src);
extern int cloneMatrix(Matrix* dist,const Matrix* src);
extern void __transpose(Matrix* dist,const Matrix* src);
extern int transpose(Matrix* dist,const Matrix* src);
extern float __det(const Matrix* mat);
extern int det(float* result,const Matrix* mat);
extern void __submatrix(Matrix* dist,const Matrix* src,int rowStart,int rowEnd,int colStart,int colEnd);
extern int submatrix(Matrix* dist,const Matrix* src,int rowStart,int rowEnd,int colStart,int colEnd);
extern float matrixGet(const Matrix* mat,const int row,const int col);
extern void matrixSet(Matrix* mat,const int row,const int col,const float num);
extern int __inverse(Matrix* dist,const Matrix* src);
extern int inverse(Matrix* dist,const Matrix* src);

#define NULL_MATRIX createMatrix(0,0,NULL)

#endif 
