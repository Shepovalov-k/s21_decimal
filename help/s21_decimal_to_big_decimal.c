#include "help.h"

s21_big_decimal s21_decimal_to_big_decimal(s21_decimal d) {
  s21_big_decimal result = {0};
  for (int i = 0; i < 3; ++i) {
    result.bits[i] = (uint32_t)d.bits[i];
  }
  result.scale_big = s21_get_scale(d);
  result.sign_big = s21_get_sign(d);
  return result;
}