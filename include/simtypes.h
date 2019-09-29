#ifndef __SIMTYPES_H__
#define __SIMTYPES_H__

#ifndef SIGN
#define SIGN 

#define SAFE
#define UNSAFE
#define UNUSABLE
#define FAST
#define OPTIMIZATION
#define DETECTION
#define PRIVATE
#define PUBLIC
#define FUNCTION_USED_BY(_FUNCTION_NAME,_DESCRIPTION)

#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

#define TRUE  1
#define FALSE 0
typedef char BOOL;

//
#define st_va

#ifndef va_list
typedef char* va_list;
#endif

#ifndef va_aligined_size
#define va_aligined_size(param) (((sizeof(param)) + (sizeof(int) - 1)) & ~((sizeof(int) - 1)))
#endif

#ifndef va_start
#define va_start(ap,param) (ap = (va_list)(((va_list)&param) + va_aligined_size(param)))
#endif

#ifndef va_arg
#define va_arg(ap,type) (*(type *) ((ap += va_aligined_size(type)) - va_aligined_size(type)))
#endif

#ifndef va_end
#define va_end(ap) (ap = ((va_list)0))
#endif

// 

#endif
