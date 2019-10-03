#ifndef __SIMTOOLS_H__
#define __SIMTOOLS_H__

#include "simtypes.h"

#ifdef C51
#define data __c51data
#define __cdecl
#endif

#include "tools/matrix.h"
#include "tools/kalman.h"
#include "tools/complex.h"
#include "tools/fft.h"
#include "tools/angle.h"

#undef data

#endif