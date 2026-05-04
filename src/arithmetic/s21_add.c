#include <stdio.h>

#include "../help/help.h"
#include "arithmetic.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_status = 0;

  int sign_1 = (s21_get_sign(value_1));
  int sign_2 = (s21_get_sign(value_2));

  s21_big_decimal big_result;
  s21_big_decimal big_v1 = s21_decimal_to_big_decimal(value_1);
  s21_big_decimal big_v2 = s21_decimal_to_big_decimal(value_2);
  s21_normalize_big(&big_v1, &big_v2);
  big_result.scale_big = big_v1.scale_big;

  s21_decimal value_1_abs = value_1;
  s21_decimal value_2_abs = value_2;
  s21_set_sign(&value_1_abs, 0);
  s21_set_sign(&value_2_abs, 0);

  if (sign_1 == sign_2) {
    s21_big_add(big_v1, big_v2, &big_result);
    big_result.sign_big = sign_1;
  } else {
    if (s21_is_less(value_1_abs, value_2_abs)) {
      s21_big_sub(big_v2, big_v1, &big_result);
      big_result.sign_big = sign_2;
    } else {
      s21_big_sub(big_v1, big_v2, &big_result);
      big_result.sign_big = sign_1;
    }
  }
  exit_status = s21_is_fit_decimal_range(&big_result);
  if (!exit_status) {
    s21_big_decimal_to_decimal(result, big_result);
  }

  return exit_status;
}
