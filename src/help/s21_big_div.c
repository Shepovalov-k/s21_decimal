#include <stdio.h>

#include "help.h"

int s21_big_int_div(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *quotient, s21_big_decimal *remainder);

int s21_big_div(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal *result) {
  if (!result) return S21_CONVERSION_ERROR;
  if (s21_is_zero_big(value_2)) return S21_DIV_BY_ZERO;

  s21_big_decimal quotient = {0};
  s21_big_decimal tmp_value_1 = value_1;
  s21_big_decimal tmp_quotient = {0};
  s21_big_decimal remainder = {0};
  int error_status = S21_OK;
  error_status =
      s21_big_int_div(tmp_value_1, value_2, &tmp_quotient, &remainder);
  s21_big_add(quotient, tmp_quotient, &quotient);

  while (!error_status && !s21_is_zero_big(remainder) &&
         (quotient.scale_big < SCALE_BIG_MAX)) {
    s21_increase_scale_big(&quotient);
    s21_increase_scale_big(&remainder);
    tmp_value_1 = remainder;
    tmp_quotient = (s21_big_decimal){0};
    remainder = (s21_big_decimal){0};

    error_status =
        s21_big_int_div(tmp_value_1, value_2, &tmp_quotient, &remainder);
    tmp_quotient.scale_big = quotient.scale_big;
    s21_big_add(quotient, tmp_quotient, &quotient);
  }

  *result = quotient;

  return error_status;
}

int s21_big_int_div(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *quotient, s21_big_decimal *remainder) {
  int error_status = S21_OK;
  for (int bit_position = 223; bit_position >= 0; bit_position--) {
    int bit = s21_big_get_bit(value_1, bit_position);
    int shift_error = s21_left_shift_big(remainder, 1);
    if (shift_error) {
      return S21_TOO_LARGE;
    }
    if (bit) {
      remainder->bits[0] |= 1;
    }
    if (s21_abs_big(*remainder, value_2) >= 0) {
      s21_big_sub(*remainder, value_2, remainder);
      s21_set_bit(quotient, bit_position, 1);
    }
  }

  if (!error_status) {
    quotient->sign_big = value_1.sign_big ^ value_2.sign_big;
  } else {
    *quotient = (s21_big_decimal){0};
  }

  return error_status;
}