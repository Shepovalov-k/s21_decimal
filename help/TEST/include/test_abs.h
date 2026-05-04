#ifndef TEST_ABS_H
#define TEST_ABS_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_abs_positive) {
  s21_decimal value = {{5, 0, 0, 0}};
  s21_decimal result;
  s21_abs(value, &result);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_abs_negative) {
  s21_decimal value = {{5, 0, 0, 0x80000000}};  // Negative sign
  s21_decimal result;
  s21_abs(value, &result);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[3], 0);  // Should be positive now
}
END_TEST

START_TEST(test_abs_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result;
  s21_abs(value, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

#endif