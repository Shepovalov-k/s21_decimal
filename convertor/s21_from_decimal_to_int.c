#include "s21_convertor.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_decimal tmp;
  memcpy(&tmp, &src, sizeof(src));
  s21_truncate(tmp, &src);
  int error = 0;

  if (dst == NULL) {
    error = 1;
  } else {
    s21_decimal temp = src;
    s21_set_scale(&temp, 0);

    int sign = s21_get_sign(src);
    unsigned value = temp.bits[0];

    if (temp.bits[1] != 0 || temp.bits[2] != 0) {
      error = 1;
    } else if ((sign && value > (unsigned)INT_MAX + 1u) ||
               (!sign && value > INT_MAX)) {
      error = 1;
    } else {
      *dst = sign ? -(int)value : (int)value;
    }
  }
  return error;
}
