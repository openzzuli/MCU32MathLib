#ifndef __KALMAN_H__
#define __KALMAN_H__

#include "../simtypes.h"
#include "matrix.h"

#ifndef __KALMAN_FILTER_DATA__
#define __KALMAN_FILTER_DATA__
struct KalmanFilterData
{
	Matrix F; //State transition matrix
	Matrix B; //Control Matrix
	Matrix X; //Current state matrix
	Matrix P; //State covariance matrix 
	Matrix H; //Transition matrix
	Matrix Q; //Noise Matrix of Prediction Model
	Matrix R; //Covariance matrix of observation noise
	
	int spaceBlockSize;
};
typedef struct KalmanFilterData KalmanFilterData;
#endif

extern int kalman(const float u,const Matrix* Z,KalmanFilterData* KFD);

#endif 
