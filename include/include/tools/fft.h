#ifndef __FFT_H__
#define __FFT_H__

#include "complex.h"
#include "../simtypes.h"

#ifndef __FFT_PARAMETER__
#define __FFT_PARAMETER__
struct fftParameter
{
	Complex* data;
	int N;
	
	PRIVATE int* order;
	PRIVATE Complex* W;
	PRIVATE Complex* invW;
};
typedef struct fftParameter fftParameter;
#endif
extern int initFFT(fftParameter* param,int* order,Complex* W,Complex* invW);
extern Complex ft(const int N,const int k,const float* data);
extern int dit_fft(Complex* result,const fftParameter* param);
extern int ifft(Complex* result,const fftParameter* param);
#endif
