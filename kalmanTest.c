#include <stdio.h>
#include <time.h>
#include "include/tools/matrix.h"
#include "include/tools/kalman.h"

/*
int main()
{
	KalmanFilterData KFD;
	
	//State transition matrix
	float FData[] = {
	  1,1,
	  0,1
	};
	Matrix F = createMatrix(2,2,FData); 
	
	//Control Matrix
	float BData[] = {
	 0,
	 0
	};
	Matrix B = createMatrix(2,1,BData);
	
	//Current state matrix
	float XData[] = {
	 0,
	 0
	};
	Matrix X = createMatrix(2,1,XData); 
	
	//State covariance matrix 
	float PData[] = {
	 1,0,
	 0,1
	};
	Matrix P = createMatrix(2,2,PData);
	
	//Noise Matrix of Prediction Model
	float QData[] = {
	 0.0001,      0,
	      0, 0.0001     
	};
	Matrix Q = createMatrix(2,2,QData);
	
	//Transition matrix
	float HData[] = {
	 1,0
	};
	Matrix H = createMatrix(1,2,HData);
	
	//Covariance matrix of observation noise
	float RData[] = {
	 1
	};
	Matrix R = createMatrix(1,1,RData); 
	
	KFD.F = F;
	KFD.B = B;
	KFD.X = X;
	KFD.P = P;
	KFD.H = H;
	KFD.Q = Q;
	KFD.R = R;
	
	//Test
	float dataSet[] = {
	-0.68,1.77,2.29,3.71,3.39,5.23,5.88,7.31,8.80,9.71,9.43,
	10.60,11.51,13.32,13.52,14.76,15.08,16.15,18.40,18.76,19.90,
	20.04,21.99,22.40,23.80,25.08,26.06,27.21,28.83,29.88,29.73,
	30.00,32.62,33.72,34.79,34.98,35.53,37.40,38.97,39.35,40.56,
	41.61,42.82,42.98,43.69,45.49,46.87,46.58,47.62,48.72,49.31,
	51.60,52.73,53.24,53.72,55.57,56.35,56.13,57.25,58.40,59.79,
	61.15,62.96,62.45,64.03,64.34,65.19,67.89,67.17,68.20,69.48,
	71.00,71.88,73.70,73.80,74.76,75.32,77.19,78.45,79.94,79.16,
	81.16,81.12,83.53,84.94,84.21,85.84,87.08,87.62,88.71,89.76,
	91.09,91.37,93.41,93.89,94.16,95.01,96.73,98.70,99.92,99.91
	};
	float ZData[1]; 
	Matrix Z = createMatrix(1,1,ZData);
	int i,flag;
	
	clock_t start,end;
	start = clock();
	
	for(i = 0; i < 101; i++){
		matrixSet(&Z,0,0,dataSet[i]);
		flag = kalman(0,&Z,&KFD);
		if(flag != SUCCESS) {
			printf("ERROR");
		}
		float X0 = matrixGet(&X,0,0);
		float X1 = matrixGet(&X,1,0);
		printf("X0 = %.2f\tX1 =  %.2f\n",X0,X1);
	}
	
	end = clock();
	double time = (double)(end - start)/CLK_TCK;
	printf("time = %f\n",time);
	
	return 0;
}
*/

