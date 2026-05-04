#include "comparison.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result;
  s21_big_decimal v1 = s21_decimal_to_big_decimal(value_1);
  s21_big_decimal v2 = s21_decimal_to_big_decimal(value_2);
  if (s21_is_zero_big(v1) && s21_is_zero_big(v2)) {
    result = 0;
  } else if (s21_is_zero_big(v1)) {
    result = !s21_get_sign(value_2);
  } else if (s21_is_zero_big(v2)) {
    result = s21_get_sign(value_1);
  } else {
    int sign1 = s21_get_sign(value_1);
    int sign2 = s21_get_sign(value_2);

    if (sign1 != sign2) {
      if (sign1 > sign2) {
        result = 1;
      } else {
        result = 0;
      }
    } else {
      s21_normalize_big(&v1, &v2);
      int cmp = s21_abs_big(v1, v2);
      if (sign1) {  // оба отрицательные
        if (cmp == 1) {
          result = 1;
        } else {
          result = 0;
        }
      } else {  // оба положительные
        if (cmp == -1) {
          result = 1;
        } else {
          result = 0;
        }
      }
    }
  }

  return result;
}
