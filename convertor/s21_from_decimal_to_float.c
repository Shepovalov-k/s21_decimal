#include "s21_convertor.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;

  if (dst == NULL) {
    error = 1;
  } else {
    *dst = 0.0f;
    if (!s21_is_zero(src)) {
      int sign = s21_get_sign(src);
      int scale = s21_get_scale(src);
      uint64_t low, middle, high;
      low = *((unsigned int *)(&(src.bits[0])));
      middle = *((unsigned int *)(&(src.bits[1])));
      high = *((unsigned int *)(&(src.bits[2])));
      double result = (double)low;
      if (src.bits[1] != 0) result += (double)middle * 4294967296.0;
      if (src.bits[2] != 0) result += (double)high * 18446744073709551616.0;

      while (scale-- > 0) {
        result = result / 10.0;
      }
      *dst = (float)(sign ? -result : result);
    }
  }
  return error;
}