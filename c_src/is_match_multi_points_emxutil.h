/*
 * is_match_multi_points_emxutil.h
 *
 * Code generation for function 'is_match_multi_points_emxutil'
 *
 * C source code generated on: Tue Jul 17 21:48:17 2012
 *
 */

#ifndef __IS_MATCH_MULTI_POINTS_EMXUTIL_H__
#define __IS_MATCH_MULTI_POINTS_EMXUTIL_H__
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
extern void emxEnsureCapacity(emxArray__common *emxArray, int32_T oldNumel, int32_T elementSize);
extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int32_T numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions);
#endif
/* End of code generation (is_match_multi_points_emxutil.h) */
