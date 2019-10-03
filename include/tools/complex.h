#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#include "../simtypes.h"

#ifndef __COMPLEX__
#define __COMPLEX__
struct Complex{
	float a;	
	float bi;
};
typedef struct Complex Complex;
#endif

extern Complex createComplex(const float a,const float b);
extern float cpabs(const Complex* c);
extern Complex cpadd(const Complex* A,const Complex* B);
extern __cdecl Complex cpsadd(const Complex* n,...);
extern Complex cpmulConst(const Complex* c,float n);
extern Complex cpmul(const Complex* A,const Complex* B);
extern Complex cpconj(const Complex* c);

#endif
