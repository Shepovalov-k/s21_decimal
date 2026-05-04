#include "help.h"

int s21_big_decimal_to_decimal(s21_decimal *dst, s21_big_decimal src) {
  if (!dst) return S21_CONVERSION_ERROR;
  s21_decimal result = {0};
  for (int i = 3; i < 7; ++i) {
    if (src.bits[i] != 0) return S21_TOO_LARGE;
  }
  for (int i = 0; i < 3; ++i) {
    result.bits[i] = (int)src.bits[i];
  }
  s21_set_scale(&result, src.scale_big);
  s21_set_sign(&result, src.sign_big);
  *dst = result;
  return S21_OK;
}