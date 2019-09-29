#include "fft.h"
#include "angle.h"
#include "complex.h"
#include "../simtypes.h"
#include "../exception.h"

#define DOUBLE_PI 6.2831853071796f

PRIVATE Complex Wnk(const int N,const int k);

Complex dit_fft(const int N,const int k,const float* data)
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

//Complex dif_fft
PRIVATE Complex Wnk(const int N,const int k)
{
	float angle = -(DOUBLE_PI / ((float)N))*((float)k);
	Complex W = {t_cos(angle),t_sin(angle)};
	return W;
}



