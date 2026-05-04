#include "comparison.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int result;
  s21_big_decimal v1 = s21_decimal_to_big_decimal(a);
  s21_big_decimal v2 = s21_decimal_to_big_decimal(b);
  if (s21_is_zero_big(v1) && s21_is_zero_big(v2)) {
    result = 1;
  } else {
    s21_normalize_big(&v1, &v2);
    result = (s21_abs_big(v1, v2) == 0 && s21_get_sign(a) == s21_get_sign(b));
  }

  return result;
}
