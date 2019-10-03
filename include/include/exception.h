#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#ifndef OVERFLOW
#define OVERFLOW      0xffff
#endif
#define NULL_POINTER  0xfffe

#define SUCCESS     0
#define ERROR_CODE  1

#define ERROR(_TYPE,_INFO,_RET) (_RET)
#define ERROR_RET(_RET) (_RET)


#define __BIT(_N) (__BIT_##_N)

#define __BIT_0 1
#define __BIT_1 2
#define __BIT_2 4
#define __BIT_3 8
#define __BIT_4 16
#define __BIT_5 32
#define __BIT_6 64
#define __BIT_7 128

#define DETECT(flag,bit,function) do{flag |= (function)?(__BIT(bit)):0;}while(0)

#endif
