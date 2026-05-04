#include <s21_convertor.h>

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;

  if (dst == NULL) {
    error = 1;
  } else {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;

    if (src < 0) {
      s21_set_sign(dst, 1);
      if (src == -2147483648) {
        dst->bits[0] = 2147483648u;
      } else {
        dst->bits[0] = -src;
      }
    } else {
      dst->bits[0] = src;
    }
  }
  return error;
}