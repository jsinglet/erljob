/*
 * fft.c
 *
 * Code generation for function 'fft'
 *
 * C source code generated on: Tue Jul 17 21:48:17 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "is_match_multi_points.h"
#include "fft.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void fft(const real_T x[44100], creal_T y[16384])
{
  real_T costab1q[4097];
  int32_T k;
  static real_T costab[8193];
  real_T sintab[8193];
  int32_T ix;
  uint32_T ju;
  int32_T iy;
  int32_T i;
  uint32_T n;
  boolean_T tst;
  real_T temp_re;
  real_T temp_im;
  int32_T iDelta;
  int32_T iDelta2;
  int32_T iheight;
  int32_T ihi;
  costab1q[0] = 1.0;
  for (k = 0; k < 2048; k++) {
    costab1q[k + 1] = cos(0.00038349519697141029 * ((real_T)k + 1.0));
  }

  for (k = 0; k < 2047; k++) {
    costab1q[k + 2049] = sin(0.00038349519697141029 * (4096.0 - ((real_T)k +
      2049.0)));
  }

  costab1q[4096] = 0.0;
  costab[0] = 1.0;
  sintab[0] = 0.0;
  for (k = 0; k < 4096; k++) {
    costab[k + 1] = costab1q[k + 1];
    sintab[k + 1] = -costab1q[4095 - k];
  }

  for (k = 0; k < 4096; k++) {
    costab[k + 4097] = -costab1q[4095 - k];
    sintab[k + 4097] = -costab1q[k + 1];
  }

  ix = 0;
  ju = 0U;
  iy = 0;
  for (i = 0; i < 16383; i++) {
    y[iy].re = x[ix];
    y[iy].im = 0.0;
    n = 16384U;
    tst = TRUE;
    while (tst) {
      n >>= 1U;
      ju ^= n;
      tst = ((int32_T)(ju & n) == 0);
    }

    iy = (int32_T)ju;
    ix++;
  }

  y[iy].re = x[ix];
  y[iy].im = 0.0;
  for (i = 0; i < 16384; i += 2) {
    temp_re = y[i + 1].re;
    temp_im = y[i + 1].im;
    y[i + 1].re = y[i].re - y[i + 1].re;
    y[i + 1].im = y[i].im - y[i + 1].im;
    y[i].re += temp_re;
    y[i].im += temp_im;
  }

  iDelta = 2;
  iDelta2 = 4;
  k = 4096;
  iheight = 16381;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      ix = i + iDelta;
      temp_re = y[ix].re;
      temp_im = y[ix].im;
      y[i + iDelta].re = y[i].re - y[ix].re;
      y[i + iDelta].im = y[i].im - y[ix].im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    ix = 1;
    for (iy = k; iy < 8192; iy += k) {
      i = ix;
      ihi = ix + iheight;
      while (i < ihi) {
        temp_re = costab[iy] * y[i + iDelta].re - sintab[iy] * y[i + iDelta].im;
        temp_im = costab[iy] * y[i + iDelta].im + sintab[iy] * y[i + iDelta].re;
        y[i + iDelta].re = y[i].re - temp_re;
        y[i + iDelta].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += iDelta2;
      }

      ix++;
    }

    k >>= 1;
    iDelta = iDelta2;
    iDelta2 <<= 1;
    iheight -= iDelta;
  }
}

/* End of code generation (fft.c) */
