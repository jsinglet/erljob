/*
 * is_match_multi_points.c
 *
 * Code generation for function 'is_match_multi_points'
 *
 * C source code generated on: Tue Jul 17 21:48:17 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "is_match_multi_points.h"
#include "is_match_multi_points_emxutil.h"
#include "fft.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
real_T is_match_multi_points(const real_T mono[44100], real_T Fs, const real_T
  keys[20], real_T threshold)
{
  real_T hits;
  static creal_T Y[16384];
  int32_T i0;
  real_T y;
  real_T Y_im;
  static real_T f[8193];
  int32_T k;
  int32_T idx;
  int8_T ii_data[20];
  int32_T ii;
  boolean_T exitg3;
  boolean_T guard2 = FALSE;
  int8_T b_ii_data[20];
  int32_T key_start;
  int8_T key_points_data[20];
  int32_T i;
  emxArray_real_T *key_hits;
  emxArray_real_T *possible_matches;
  emxArray_boolean_T *x;
  int32_T i1;
  int32_T j;
  boolean_T bv0[8193];
  boolean_T bv1[8193];
  int32_T b_idx;
  int16_T c_ii_data[8193];
  int16_T ii_size[2];
  boolean_T exitg2;
  boolean_T guard1 = FALSE;
  int32_T tmp_data[8193];
  int16_T d_ii_data[8193];
  boolean_T exitg1;

  /* some comments are required here */
  /*  mono      - the single mono track audio */
  /*  Fs        - the sampling rate of the track */
  /*  keys      - a simple integer data structure representing keys. Format is */
  /*  as follows:  */
  /*    */
  /*  [f1,f2,f3, 0, g1,g2,g3, -1.....] -- where f and g are different keys */
  /*   */
  /*  Note that the number of points must be symetric.  */
  /*  */
  /*  threshold - the minimum spectral density of a match */
  /*  2^nextpow2(length(mono)); % */
  fft(mono, Y);
  for (i0 = 0; i0 < 16384; i0++) {
    y = Y[i0].re * Y[i0].re - Y[i0].im * -Y[i0].im;
    Y_im = Y[i0].re * -Y[i0].im + Y[i0].im * Y[i0].re;
    if (Y_im == 0.0) {
      Y[i0].re = y / 16384.0;
      Y[i0].im = 0.0;
    } else if (y == 0.0) {
      Y[i0].re = 0.0;
      Y[i0].im = Y_im / 16384.0;
    } else {
      Y[i0].re = y / 16384.0;
      Y[i0].im = Y_im / 16384.0;
    }
  }

  y = Fs / 2.0;
  f[8192] = 1.0;
  f[0] = 0.0;
  for (k = 0; k < 8191; k++) {
    f[1 + k] = (1.0 + (real_T)k) * 0.0001220703125;
  }

  for (i0 = 0; i0 < 8193; i0++) {
    f[i0] *= y;
  }

  idx = 0;
  ii = 1;
  exitg3 = FALSE;
  while ((exitg3 == 0U) && (ii < 21)) {
    guard2 = FALSE;
    if (keys[ii - 1] == 0.0) {
      idx++;
      ii_data[idx - 1] = (int8_T)ii;
      if (idx >= 20) {
        exitg3 = TRUE;
      } else {
        guard2 = TRUE;
      }
    } else {
      guard2 = TRUE;
    }

    if (guard2 == TRUE) {
      ii++;
    }
  }

  if (1 > idx) {
    idx = 0;
  }

  key_start = idx - 1;
  for (i0 = 0; i0 <= key_start; i0++) {
    b_ii_data[i0] = ii_data[i0];
  }

  key_start = idx - 1;
  for (i0 = 0; i0 <= key_start; i0++) {
    ii_data[i0] = b_ii_data[i0];
  }

  key_start = idx - 1;
  for (i0 = 0; i0 <= key_start; i0++) {
    key_points_data[i0] = ii_data[i0];
  }

  key_start = 1;
  hits = 0.0;

  /*  for each key, loop through and extract this key. */
  i = 0;
  emxInit_real_T(&key_hits, 2);
  emxInit_real_T(&possible_matches, 2);
  emxInit_boolean_T(&x, 2);
  while (i <= idx - 1) {
    /*  extract the key */
    if (key_start > key_points_data[i] - 1) {
      i0 = 0;
      i1 = 1;
    } else {
      i0 = key_start - 1;
      i1 = key_points_data[i];
    }

    k = key_hits->size[0] * key_hits->size[1];
    key_hits->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)key_hits, k, (int32_T)sizeof(real_T));
    k = key_hits->size[0] * key_hits->size[1];
    key_hits->size[1] = (i1 - i0) - 1;
    emxEnsureCapacity((emxArray__common *)key_hits, k, (int32_T)sizeof(real_T));
    key_start = (i1 - i0) - 1;
    key_start--;
    for (k = 0; k <= key_start; k++) {
      key_hits->data[k] = 0.0;
    }

    /*  for each key, find matches. */
    for (j = 0; j <= (i1 - i0) - 2; j++) {
      /*  fprintf('Looking at Key: %d\n', key(j)); */
      for (k = 0; k < 8193; k++) {
        bv0[k] = (f[k] >= keys[i0 + j] - 100.0);
        bv1[k] = (f[k] <= keys[i0 + j] + 100.0);
      }

      b_idx = 0;
      for (k = 0; k < 2; k++) {
        ii_size[k] = (int16_T)(1 + (k << 13));
      }

      ii = 1;
      exitg2 = FALSE;
      while ((exitg2 == 0U) && (ii < 8194)) {
        guard1 = FALSE;
        if (bv0[ii - 1] && bv1[ii - 1]) {
          b_idx++;
          c_ii_data[b_idx - 1] = (int16_T)ii;
          if (b_idx >= 8193) {
            exitg2 = TRUE;
          } else {
            guard1 = TRUE;
          }
        } else {
          guard1 = TRUE;
        }

        if (guard1 == TRUE) {
          ii++;
        }
      }

      if (1 > b_idx) {
        b_idx = 0;
      }

      key_start = b_idx - 1;
      for (k = 0; k <= key_start; k++) {
        tmp_data[k] = 1 + k;
      }

      key_start = b_idx - 1;
      for (k = 0; k <= key_start; k++) {
        ii = 0;
        while (ii <= 0) {
          d_ii_data[k] = c_ii_data[tmp_data[k] - 1];
          ii = 1;
        }
      }

      ii_size[0] = 1;
      ii_size[1] = (int16_T)b_idx;
      key_start = b_idx - 1;
      for (k = 0; k <= key_start; k++) {
        c_ii_data[k] = d_ii_data[k];
      }

      k = possible_matches->size[0] * possible_matches->size[1];
      possible_matches->size[0] = 1;
      possible_matches->size[1] = ii_size[1];
      emxEnsureCapacity((emxArray__common *)possible_matches, k, (int32_T)sizeof
                        (real_T));
      key_start = ii_size[1] - 1;
      for (k = 0; k <= key_start; k++) {
        possible_matches->data[k] = (real_T)c_ii_data[k];
      }

      for (key_start = 0; key_start <= possible_matches->size[1] - 1; key_start
           ++) {
        if (Y[(int32_T)possible_matches->data[key_start] - 1].re >= threshold) {
          /*  one more hit -- every key must be hit at least once. */
          key_hits->data[j]++;
        }
      }
    }

    /*  after looking at this entire key, if there aren't any keys that */
    /*  didn't hit, see if we want to up the max */
    i0 = x->size[0] * x->size[1];
    x->size[0] = 1;
    x->size[1] = key_hits->size[1];
    emxEnsureCapacity((emxArray__common *)x, i0, (int32_T)sizeof(boolean_T));
    key_start = key_hits->size[0] * key_hits->size[1] - 1;
    for (i0 = 0; i0 <= key_start; i0++) {
      x->data[i0] = (key_hits->data[i0] == 0.0);
    }

    key_start = x->size[1];
    if (1 <= key_start) {
      k = 1;
    } else {
      k = key_start;
    }

    b_idx = 0;
    ii = 1;
    exitg1 = FALSE;
    while ((exitg1 == 0U) && (ii <= key_start)) {
      if (x->data[ii - 1]) {
        b_idx = 1;
        exitg1 = TRUE;
      } else {
        ii++;
      }
    }

    if (k == 1) {
      if (b_idx == 0) {
        k = 0;
      }
    } else {
      if (1 > b_idx) {
        i0 = -1;
      } else {
        i0 = 0;
      }

      k = i0 + 1;
    }

    if (k == 0) {
      if (key_hits->size[1] == 0) {
        y = 0.0;
      } else {
        key_start = key_hits->size[1];
        y = key_hits->data[0];
        for (k = 2; k <= key_start; k++) {
          y += key_hits->data[k - 1];
        }
      }

      if (y > hits) {
        if (key_hits->size[1] == 0) {
          hits = 0.0;
        } else {
          key_start = key_hits->size[1];
          hits = key_hits->data[0];
          for (k = 2; k <= key_start; k++) {
            hits += key_hits->data[k - 1];
          }
        }
      }
    }

    /*  update the key position */
    key_start = key_points_data[i] + 1;
    i++;
  }

  emxFree_boolean_T(&x);
  emxFree_real_T(&possible_matches);
  emxFree_real_T(&key_hits);
  return hits;
}

/* End of code generation (is_match_multi_points.c) */
