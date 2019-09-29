#include <stdio.h>
#include <math.h>
#include <time.h>
#define PI 3.1415926f
#include "include/tools/complex.h"
#include "include/exception.h"
#include "include/tools/angle.h"
/*
int main(){
	
	float angle;
	float sinx,t_sinx,dsinx;
	
	int i,t = 1000;
	clock_t start,end;
	double t0,t1;
	double ft0,ft1;
	
	sinx = sin(1);
	t_sinx = t_sin(1);
	
	int times = 100;
	
	for(angle = -5*PI; angle <= 5*PI ; angle += 0.01){
		sinx = sin(angle);
		t_sinx = t_sin(angle);
		dsinx = sinx - t_sinx;
		printf("%f %f %f\n",sinx,t_sinx,dsinx);
	}
	
	

test:	
	start = clock();
	for(i = 0 ; i < t; i ++)
	for(angle = -5*PI; angle <= 5*PI ; angle += 0.01){
		sinx = sin(angle);
	}
	end = clock();
	t0 = (double)(end - start)/CLK_TCK;
	
	start = clock();
	for(i = 0 ; i < t; i ++)
	for(angle = -5*PI; angle <= 5*PI ; angle += 0.01){
		sinx = t_sin(angle);
	}
	end = clock();
	t1 = (double)(end - start)/CLK_TCK;
	
	printf("t0 = %f,t1 = %f\n",t0,t1);
	ft0 += t0;
	ft1 += t1;
	times--;
	if(times) goto test;
	
	printf("***************************\n");
	printf("ft0 = %f,ft1 = %f\n",ft0/100.0,ft1/100.0);
	
	return 0;
}
*/

