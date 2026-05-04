#ifndef TEST_IS_ZERO_BIG_H
#define TEST_IS_ZERO_BIG_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_zero_big_decimal) {
  s21_big_decimal d = {0};
  ck_assert_int_eq(s21_is_zero_big(d), 1);
}
END_TEST

START_TEST(test_non_zero_big_decimal) {
  s21_big_decimal d = {0};
  d.bits[0] = 1;
  ck_assert_int_eq(s21_is_zero_big(d), 0);

  s21_big_decimal d2 = {0};
  d2.bits[6] = 1;
  ck_assert_int_eq(s21_is_zero_big(d2), 0);

  s21_big_decimal d3 = {0};
  d3.bits[3] = 1;
  ck_assert_int_eq(s21_is_zero_big(d3), 0);
}
END_TEST

START_TEST(test_mixed_big_decimal) {
  s21_big_decimal d = {0};
  for (int i = 0; i < 7; i++) {
    if (!(i % 2)) {
      d.bits[i] = 1;
      ck_assert_int_eq(s21_is_zero_big(d), 0);
    }
    d.bits[i] = 0;
    ck_assert_int_eq(s21_is_zero_big(d), 1);
  }
}
END_TEST

#endif