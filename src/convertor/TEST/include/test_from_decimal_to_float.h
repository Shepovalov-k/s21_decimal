#ifndef TEST_FROM_DECIMAL_TO_FLOAT_H
#define TEST_FROM_DECIMAL_TO_FLOAT_H

#include <check.h>
#include <float.h>
#include <limits.h>
#include <stdlib.h>

#include "s21_decimal.h"

START_TEST(test_from_decimal_to_float_positive) {
  s21_decimal value = {{123456, 0, 0, 0x30000}};
  float f = 123.456;
  float result;

  int status = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq_tol(result, f, 1e-6);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_from_decimal_to_float_negative) {
  s21_decimal value = {{78901, 0, 0, 0x80030000}};
  float result;
  float expected = -78.901;

  int status = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq_tol(result, expected, 1e-6);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_from_decimal_to_float_zero) {
  s21_decimal dec;
  float res;

  s21_from_int_to_decimal(0, &dec);
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &res), 0);
  ck_assert_float_eq(res, 0.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_null) {
  s21_decimal dec;
  s21_from_int_to_decimal(0, &dec);

  ck_assert_int_eq(s21_from_decimal_to_float(dec, NULL), 1);
}
END_TEST

START_TEST(test_from_decimal_to_float_max) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  float result;
  float expected = 7.922816251426434e+28;

  int status = s21_from_decimal_to_float(value, &result);

  ck_assert_float_eq_tol(result, expected, 1e13);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_from_decimal_to_float_min) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  float result;
  float expected = -7.922816251426434e+28;

  int status = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq_tol(result, expected, 1e13);
  ck_assert_int_eq(status, 0);
}
END_TEST

#endif