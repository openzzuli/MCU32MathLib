#include "fft.h"
#include "angle.h"
#include "complex.h"
#include "../simtypes.h"
#include "../exception.h"

#include <math.h>

#define DOUBLE_PI 6.2831853071796f

PRIVATE static __inline__ Complex Wnk(const int N,const int k);
PRIVATE static __inline__ void orderData(Complex* result,const fftParameter* param);
PRIVATE void __fft(Complex* result,const fftParameter* param,const BOOL inv);
PRIVATE void orderDataByOrderArray(Complex* result,const Complex *data,int* array,const int N);

int initFFT(fftParameter* param,int* order,Complex* W,Complex* invW)
{
	const int N = param->N;
	int i;
	
	int bits = 0,tN = N>>1;
	while(++bits&&(tN>>=1));
	int now,number,sign;
	
	for(i = 0; i < N; i++)
	{
		now = i;
		number = 0;
		for(sign = 0; sign < bits ; sign++){
			number <<= 1;
			number |= now & 1;
			now >>= 1;
		}
		order[i] = number;
		W[i] = Wnk(N,i);
		invW[i] = cpconj(&W[i]);
	}
	
	param->order = order;
	param->W = W;
	param->invW = invW;
}

//
Complex ft(const int N,const int k,const float* data)
{
	if(k == 0){
		Complex r = {0,0};
		return r;
	}
	int i;
	Complex W, unit ,result = {data[0],0};
	
	for(i = 1; i < N ; i ++)
	{
		W = Wnk(N,k*i);
		unit = cpmulConst(&W,data[i]);
		result.a += unit.a;
		result.bi += unit.bi;
	}
	return result;
}

/* 
 * DIT FFT
 * input :
 * Param 1 (result): result complex number array pointer
 * Param 2 (param): FFT Parameter
 */
int dit_fft(Complex* result,const fftParameter* param)
{	
	__fft(result,param,FALSE);
	return SUCCESS;
}

PRIVATE void __fft(Complex* result,const fftParameter* param,const BOOL inv)
{
	const int N = param->N;
	const Complex* W = inv?param->invW:param->W;
	Complex* orderedData = result;
	Complex* data;
	Complex inner;
	
	orderData(orderedData,param);
	
	int interval,size,index;
	const Complex *end = orderedData + N;
	for( interval = 2 ; interval <= N; interval <<= 1 ){
		size = interval >> 1;
		for(data = orderedData ; data != end ; data += interval ){
			for(index = 0;index < size;index ++){
				inner = cpmul(&(W[N/interval*index]),&(data[index+size]));
				
				data[index + size].a  = data[index].a - inner.a;
				data[index + size].bi = data[index].bi - inner.bi;
	            data[index].a  += inner.a;
	            data[index].bi += inner.bi;
			}
		}
	}
	
} FUNCTION_USED_BY(dit_fft,"DIT FFT butterfly operation");

PRIVATE static __inline__ Complex Wnk(const int N,const int k)
{
	float angle = -(DOUBLE_PI / ((float)N))*((float)k);
	Complex W = {cos(angle),sin(angle)};
	return W;
}

PRIVATE static __inline__ void orderData(Complex* result,const fftParameter* param)
{
	orderDataByOrderArray(result,param->data,param->order,param->N);
}

PRIVATE void orderDataByOrderArray(Complex* result,const Complex *data,int* array,const int N)
{
	int i,s;
	for(i = 0; i < N; i++)
	{
		s = array[i];
		result[i].a  =  data[s].a;
		result[i].bi =  data[s].bi;
	}
	
}

/*
 * IFFT
 * input :
 * Param 1 (result): result complex number array pointer
 * Param 2 (param): FFT Parameter
 */
int ifft(Complex* result,const fftParameter* param)
{
	__fft(result,param,TRUE);
	const int N = param->N;
	const float iN = 1.0f/N;
	int i;
	for(i = 0; i < N; i++){
		result[i].a  *= iN;
		result[i].bi *= iN;
	}
	return SUCCESS;
}

