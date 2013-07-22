/*
 * fft.h
 *
 * Code generation for function 'fft'
 *
 * C source code generated on: Tue Jul 17 21:48:17 2012
 *
 */

#ifndef __FFT_H__
#define __FFT_H__
/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "rtwtypes.h"
#include "is_match_multi_points_types.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern void fft(const real_T x[44100], creal_T y[16384]);
#endif
/* End of code generation (fft.h) */
