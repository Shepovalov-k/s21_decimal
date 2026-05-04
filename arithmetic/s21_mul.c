#include <stdio.h>

#include "arithmetic.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) return S21_CONVERSION_ERROR;
  int error_status = S21_OK;

  int scale_1 = s21_get_scale(value_1);
  int scale_2 = s21_get_scale(value_2);
  int result_scale = scale_1 + scale_2;
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  int result_sign = sign_1 ^ sign_2;

  s21_big_decimal big_v1 = s21_decimal_to_big_decimal(value_1);
  s21_big_decimal big_v2 = s21_decimal_to_big_decimal(value_2);
  s21_big_decimal big_result = {0};

  if (s21_is_zero(value_1) || s21_is_zero(value_2)) {
    *result = (s21_decimal){0};
    s21_set_scale(result, result_scale);
    s21_set_sign(result, result_sign);
    return S21_OK;
  }

  s21_big_mul(big_v1, big_v2, &big_result);

  error_status = s21_is_fit_decimal_range(&big_result);
  if (!error_status) {
    error_status = s21_big_decimal_to_decimal(result, big_result);
  }

  return error_status;
}