#include <stdio.h>
#include "include/tools/matrix.h"

#define TEST(FUNCTION_NAME)
void printLine()
{
	printf("**************************\n");
}
void printMatrix(const Matrix* mat)
{
	int i,j;
	for(i = 0; i < mat->rows; i++){
		for(j = 0; j < mat->cols ; j++){
			printf("%5.2f  ",mat->data[i*mat->cols + j]);
		}
		printf("\n");
	}
	printf("\n");
}

TEST(createMatrix);
void create()
{
	printLine();
	printf("创建一个3x3的矩阵:\n");
	float data3X3[] = {
		1.0,2.0,3.0,
		4.0,5.0,6.0,
		7.0,8.0,9.0
	};
	Matrix mat = createMatrix(3,3,data3X3);
	printMatrix(&mat);
}


TEST(inverse);
void inv(){
	printLine();
	printf("对矩阵A求逆矩阵:\n");
	float data4X4[] = {
	 1  ,   2 ,    3  ,   4,
     5  ,   5 ,    6  ,   7,
     8  ,   9 ,   10  ,  11,
    12  ,  13 ,    2  ,   5
	};
	float out4X4[16];
	Matrix A = createMatrix(4,4,data4X4);
	Matrix iA = createMatrix(4,4,out4X4);
	inverse(&iA,&A);
	
	printf("矩阵A:\n");
	printMatrix(&A);
	printf("矩阵A的逆矩阵:\n");
	printMatrix(&iA);
}

TEST(det);
void detMatrix()
{
	printLine();
	printf("对矩阵A求行列式的值:\n");
	float data4X4[] = {
	 1  ,   2 ,    3  ,   4,
     5  ,   5 ,    6  ,   7,
     8  ,   9 ,   10  ,  11,
    12  ,  13 ,    2  ,   5
	};
	Matrix A = createMatrix(4,4,data4X4);
	float detA;
	det(&detA,&A);
	
	printf("矩阵A:\n");
	printMatrix(&A);	
	printf("det(A) = %f\n",detA);
}

TEST(transpose)
void trans()
{
	printLine();
	printf("求矩阵A的转置:\n");
	
	float data2X3[] = {
		2.0,4.0,2.5,
		3.5,6.0,8.0
	};
	float data3X2[6];
	Matrix A = createMatrix(2,3,data2X3);
	Matrix AT = createMatrix(3,2,data3X2);
	transpose(&AT,&A); 
	
	printf("矩阵A:\n");
	printMatrix(&A);
	printf("矩阵转置:\n");
	printMatrix(&AT);
}

TEST(mul);
void matrixMul()
{
	printLine();
	printf("求矩阵A与矩阵B做乘法的结果:\n");
	
	float data2X3[] = {
		2.0,4.0,
		2.5,3.5,
		6.0,8.0
	};
	
	float data3X2[] = {
		2.0,4.0,5.0,
		1.0,3.0,7.0
	};
	
	float data2X2[4];
	
	Matrix A = createMatrix(2,3,data2X3);
	Matrix B = createMatrix(3,2,data3X2);
	Matrix result = createMatrix(2,2,data2X2);
	
	mul(&result,&A,&B);
	
	printf("矩阵A:\n");
	printMatrix(&A);
	printf("矩阵B:\n");
	printMatrix(&B);
	printf("A*B:\n");
	printMatrix(&result);
}

TEST(mulConst)
void matrixMulConst()
{
	printLine();
	printf("求矩阵A乘以常数:\n");
	
	float data2X3[] = {
		2.0,4.0,2.5,
		3.5,6.0,8.0
	};
	float rdata2X3[6];
	Matrix A = createMatrix(2,3,data2X3);
	Matrix result = createMatrix(2,3,rdata2X3);
	mulConst(&result,&A,5); 
	printf("常数:5\n\n");
	printf("矩阵A:\n");
	printMatrix(&A);
	printf("计算结果:\n");
	printMatrix(&result);
}

TEST(add)
void matrixPlus()
{
	printLine();
	printf("求矩阵A与矩阵B的和:\n");
	
	float dataA[] = {
		1.0,2.0,3.0,
		4.0,5.0,6.0,
		7.0,8.0,9.0
	};
	
	float dataB[] = {
		9.0,8.0,7.0,
		6.0,5.0,4.0,
		3.0,2.0,1.0
	};
	
	float data3X3[9];
	
	Matrix A = createMatrix(3,3,dataA);
	Matrix B = createMatrix(3,3,dataB);
	Matrix result = createMatrix(3,3,data3X3);
	add(&result,&A,&B);
	
	printf("矩阵A:\n");
	printMatrix(&A);
	printf("矩阵B:\n");
	printMatrix(&B);
	printf("计算结果:\n");
	printMatrix(&result);
}

TEST(cloneMatrix)
void copy()
{
	float dataA[] = {
		1.0,2.0,3.0,
		4.0,5.0,6.0,
		7.0,8.0,9.0
	};
	float data3X3[9];
	Matrix mat = createMatrix(3,3,dataA);
	Matrix clone = createMatrix(3,3,data3X3);
	cloneMatrix(&clone,&mat);
}

TEST(matrixGet)
TEST(matrixSet)
void setterAndGetter()
{
	float dataA[] = {
		1.0,2.0,3.0,
		4.0,5.0,6.0,
		7.0,8.0,9.0
	};
	Matrix A = createMatrix(3,3,dataA);
	float n = matrixGet(&A,1,2);
	matrixSet(&A,1,1,3.0);
}

TEST(submatrix)
void sub()
{
	printLine();
	printf("求矩阵A的子矩阵(第2行到第3行，第3列到第3列):\n");
	
	float dataA[] = {
		1.0,2.0,3.0,
		4.0,5.0,6.0,
		7.0,8.0,9.0
	};
	float data2X1[2];
	Matrix A = createMatrix(3,3,dataA);
	Matrix sub = createMatrix(2,1,dataA);
	// 行 : 从 1 开始 不包括 3
	// 列 : 从 2 开始 不包括 3 
	submatrix(&sub,&A,1,3,2,3);
	
	printf("矩阵A:\n");
	printMatrix(&A);
	printf("子矩阵:\n");
	printMatrix(&sub);
}
/*
int main(){
	
	//如何创建矩阵 
	create();
	//如何对矩阵求逆
	inv(); 
	//如何求行列式的值 
	detMatrix();
	//如何转置 
	trans();
	//如何做矩阵乘积 
	matrixMul();
	//如何做矩阵乘以常数 
	matrixMulConst(); 
	//如何做矩阵加法
	matrixPlus();
	//如何复制矩阵 
	copy(); 
	//如何取或者设置矩阵的某一行某一列值 
	setterAndGetter();
	//如何取子矩阵
	sub();
	
	return 0;	
}
*/
