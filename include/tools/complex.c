#include <math.h>
#include "complex.h"
#include "../simtypes.h"
#include "../exception.h"

Complex createComplex(const float a,const float b)
{
	Complex ret;
	ret.a  = a;
	ret.bi = b;
	return ret;
}

float cpabs(const Complex* c)
{
	float a2 = (c->a)*(c->a);
	float b2 = (c->bi)*(c->bi);
	return sqrt(a2+b2);
}

Complex cpadd(const Complex* A,const Complex* B)
{
	Complex ret = {
	A->a + B->a,
	A->bi + B->bi
	};
	return ret;
}

__cdecl Complex cpsadd(const Complex* n,...)
{
	va_list args;
	va_start(args,n);
	
	Complex* c;
	Complex result;
	
	float* a  = &(result.a);
	float* bi = &(result.bi);
	
	for( c = ((Complex*)n);c;c = va_arg(args,Complex*)){	
		*a  += c->a;
		*bi += c->bi;
	}
	
	va_end(args);
	return result;
}

Complex cpmulConst(const Complex* c,float n)
{
	Complex ret = {(c->a)*n,(c->bi)*n};
	return ret;
}

Complex cpmul(const Complex* A,const Complex* B)
{
	Complex ret = {
		(A->a*B->a) - (A->bi*B->bi),
		(A->a*B->bi) + (A->bi*B->a)
	};
	return ret;
}

Complex cpconj(const Complex* c)
{
	Complex ret = {
		c->a,-c->bi
	};
	return ret;
}
