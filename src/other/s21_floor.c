#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;
  s21_truncate(value, result);
  int scale = s21_get_scale(value);
  if (scale > 0 && s21_get_sign(value)) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_sub(*result, one, result);
  }
  return 0;
}
