#include <stdio.h>

#include "../help/help.h"
#include "arithmetic.h"
#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal minus_value_2 = {{0}};
  s21_negate(value_2, &minus_value_2);
  return s21_add(value_1, minus_value_2, result);
}