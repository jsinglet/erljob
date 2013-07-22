/*
 * is_match_multi_points_types.h
 *
 * Code generation for function 'is_match_multi_points'
 *
 * C source code generated on: Tue Jul 17 21:48:17 2012
 *
 */

#ifndef __IS_MATCH_MULTI_POINTS_TYPES_H__
#define __IS_MATCH_MULTI_POINTS_TYPES_H__

/* Type Definitions */
#ifndef struct_emxArray__common
#define struct_emxArray__common
typedef struct emxArray__common
{
    void *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
} emxArray__common;
#endif
#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T
typedef struct emxArray_boolean_T
{
    boolean_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
} emxArray_boolean_T;
#endif
#ifndef struct_emxArray_int32_T_1x8193
#define struct_emxArray_int32_T_1x8193
typedef struct emxArray_int32_T_1x8193
{
    int32_T data[8193];
    int32_T size[2];
} emxArray_int32_T_1x8193;
#endif
#ifndef struct_emxArray_int32_T_20
#define struct_emxArray_int32_T_20
typedef struct emxArray_int32_T_20
{
    int32_T data[20];
    int32_T size[1];
} emxArray_int32_T_20;
#endif
#ifndef struct_emxArray_int32_T_8193
#define struct_emxArray_int32_T_8193
typedef struct emxArray_int32_T_8193
{
    int32_T data[8193];
    int32_T size[1];
} emxArray_int32_T_8193;
#endif
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
typedef struct emxArray_real_T
{
    real_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
} emxArray_real_T;
#endif

#endif
/* End of code generation (is_match_multi_points_types.h) */
