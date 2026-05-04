#ifndef TEST_FROM_DECIMAL_TO_FLOAT_H
#define TEST_FROM_DECIMAL_TO_FLOAT_H

#include <check.h>
#include <float.h>
#include <limits.h>
#include <stdlib.h>

#include "s21_decimal.h"

START_TEST(test_is_zero_zero_dec) {
  s21_decimal zero_dec = {0};
  ck_assert_int_eq(s21_is_zero(zero_dec), 1);
}
END_TEST
#endif