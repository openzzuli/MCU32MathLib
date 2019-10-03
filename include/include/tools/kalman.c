#include "kalman.h"
#include "matrix.h"
#include "../simtypes.h"
#include "../exception.h"

PRIVATE int ABAt(Matrix* result,const Matrix* B,const Matrix* A);
PRIVATE void eye(Matrix* mat,int n);
PRIVATE int maxRows(const KalmanFilterData* KFD);
PRIVATE int maxCols(const KalmanFilterData* KFD);

/* 
 * Kalman Filter
 * input : 
 * Param 1 (u)   : Control Variable
 * Param 2 (Z)   : Observed Data Matrix Pointer
 * Param 3 (KFD) : Kalman Filter Data
 */
DETECTION int kalman(const float u,const Matrix* Z,KalmanFilterData* KFD)
{
	int flag = 0;
	int rows,cols,size;
	if(!(KFD->spaceBlockSize)){
		rows = maxRows(KFD);
		cols = maxCols(KFD);
		size = rows*cols;
		KFD->spaceBlockSize = size;
	}else {
		size = KFD->spaceBlockSize;
	}
	float tmp0Data[size],tmp1Data[size];
	Matrix tmp0 = createMatrix(0,0,tmp0Data);
	Matrix tmp1 = createMatrix(0,0,tmp1Data);
	
	//X_ = F*X + B*u
	rows = (KFD->X).rows;
	cols = (KFD->X).cols;
	float X_Data[rows*cols];
	Matrix X_ = createMatrix(rows,cols,X_Data);
	
	DETECT(flag,0,mul(&tmp0,&(KFD->F),&(KFD->X))); //tmp0 = F*X
	DETECT(flag,1,mulConst(&tmp1,&(KFD->B),u));    //tmp1 = B*u
	DETECT(flag,2,add(&X_,&tmp0,&tmp1));           //X_ = tmp0 + tmp1
	
	if(flag) {
		return ERROR("PROCESS ERROR",
		"STEP 1 ERROR: X_ = F*X + B*u",
		0x100|flag);
	}
	
	//P_ = F*P*F' + Q
	rows = (KFD->P).rows;
	cols = (KFD->P).cols;
	float P_Data[rows*cols];
	Matrix P_ = createMatrix(rows,cols,P_Data);
	
	DETECT(flag,0,ABAt(&tmp0,&(KFD->P),&(KFD->F))); //tmp0 = F*P*F'
	DETECT(flag,1,add(&P_,&tmp0,&(KFD->Q)));        //P_ = tmp0 + Q
	
	if(flag) {
		return ERROR("PROCESS ERROR",
		"STEP 2 ERROR: P_ = F*P*F' + Q",
		0x200|flag);
	}
	
	//K = P_*H'*(H*P_*H' + R)^(-1)
	rows = (KFD->H).rows;
	cols = (KFD->H).cols;
	float KData[rows*cols],HtData[rows*cols];
	Matrix K = createMatrix(cols,rows,KData);
	Matrix Ht = createMatrix(rows,cols,HtData);
	
	DETECT(flag,0,transpose(&Ht,&(KFD->H)));   //Ht = H'
	DETECT(flag,1,ABAt(&tmp0,&P_,&(KFD->H)));  //tmp0 = H*P_*H'
	DETECT(flag,2,add(&tmp1,&tmp0,&(KFD->R))); //tmp1 = tmp0 + R
	DETECT(flag,3,inverse(&tmp0,&tmp1));       //tmp0 = (tmp1)^(-1)
	DETECT(flag,4,mul(&tmp1,&P_,&Ht));         //tmp1 = P_*H'		
	DETECT(flag,5,mul(&K,&tmp1,&tmp0));        //K = tmp1*tmp0 
	
	if(flag) {
		return ERROR("PROCESS ERROR",
		"STEP 3 ERROR: K = P_*H'*(H*P_*H' + R)^(-1)",
		0x300|flag);
	}
	
	//X = X_ + K*(Z - H*X_)
	DETECT(flag,0,mul(&tmp0,&(KFD->H),&X_));       //tmp0 = H*X_
	DETECT(flag,1,mulConst(&tmp1,&tmp0,-1));       //tmp1 = tmp0*(-1)
	DETECT(flag,2,add(&tmp0,Z,&tmp1));             //tmp0 = Z + tmp1
	DETECT(flag,3,mul(&tmp1,&K,&tmp0));            //tmp1 = K*tmp0
	DETECT(flag,4,add(&(KFD->X),&X_,&tmp1));       //X = X_ + tmp1
	
	if(flag) {
		return ERROR("PROCESS ERROR",
		"STEP 4 ERROR: X = X_ + K*(Z - H*X_)",
		0x400|flag);
	}
	
	//P = (I - K*H)*P_
	rows = K.rows;
	float IData[rows*rows];
	Matrix I = createMatrix(rows,rows,IData);
	
	eye(&I,I.rows);                                //I = I (identity matrix)
	DETECT(flag,0,mul(&tmp0,&K,&(KFD->H)));        //tmp0 = K*H
	DETECT(flag,1,mulConst(&tmp1,&tmp0,-1));       //tmp1 = tmp0*(-1)
	DETECT(flag,2,add(&tmp0,&I,&tmp1));            //tmp0 = I + tmp1
	DETECT(flag,3,mul(&(KFD->P),&tmp0,&P_));       //P = tmp0*P_ 
	
	if(flag) {
		return ERROR("PROCESS ERROR",
		"STEP 5 ERROR: P = (I - K*H)*P_",
		0x500|flag);
	}
	
	return SUCCESS;
}

PRIVATE int ABAt(Matrix* result,const Matrix* B,const Matrix* A)
{
	int flag = 0;
	float tmpData[(A->rows)*(B->cols)],AtData[(A->cols)*(A->rows)];
	Matrix tmp = createMatrix(A->rows,B->cols,tmpData);
	Matrix At = createMatrix(A->cols,A->rows,AtData);
	
	flag += transpose(&At,A);    //At = A'
	flag += mul(&tmp,A,B);       //tmp = A*B
	flag += mul(result,&tmp,&At); //result = tmp*A'
	return flag;
}

PRIVATE void eye(Matrix* mat,int n)
{
	mat->rows = n;
	mat->cols = n;
	int size = n*n;
	int i;
	for(i = 0; i < size; i++){
		mat->data[i] = 0;
	}
	for(i = 0; i < n ; i ++){
		mat->data[i*n+i] = 1;
	}
}

PRIVATE int maxRows(const KalmanFilterData* KFD)
{
	return (KFD->F).rows * 2;
}

PRIVATE int maxCols(const KalmanFilterData* KFD)
{
	return (KFD->F).rows * 2;
}

