#ifndef TEST_FROM_FLOAT_TO_DECIMAL_H
#define TEST_FROM_FLOAT_TO_DECIMAL_H

#include <check.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

START_TEST(test_positive_float_conversion) {
  s21_decimal result;
  s21_decimal expected = {{123456, 0, 0, 0x30000}};
  float f = 123.456f;

  int status = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_negative_float_conversion) {
  s21_decimal result;
  s21_decimal expected = {{123457, 0, 0, 0x80030000}};
  float f = -123.457f;

  int status = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_big_digit_count_float_conversion) {
  s21_decimal result;
  s21_decimal expected = {{1234576, 0, 0, 0x40000}};
  float f = 123.4575821f;

  int status = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_big_digit_count_float_int_conversion) {
  s21_decimal result;
  s21_decimal expected = {{1556253000, 0, 0, 0x00000}};
  float f = 1556252595.0f;

  int status = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_big_digit_count_float_negative_exp_conversion) {
  s21_decimal result;
  s21_decimal expected = {{2152106, 0, 0, 0xD0000}};
  float f = 2.1521056e-7f;

  int status = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_zero_conversion) {
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};

  int status = s21_from_float_to_decimal(0.0f, &result);

  ck_assert_mem_eq(&result, &expected, sizeof(expected));
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_small_number_conversion) {
  s21_decimal result;

  int status = s21_from_float_to_decimal(1e-29f, &result);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_large_number_conversion) {
  s21_decimal result;

  int status = s21_from_float_to_decimal(1e29f, &result);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_nan_conversion) {
  s21_decimal result;

  int status = s21_from_float_to_decimal(0.0f / 0.0f, &result);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_inf_conversion) {
  s21_decimal result;

  int status = s21_from_float_to_decimal(1.0f / 0.0f, &result);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_null_pointer_conversion) {
  float f = 1.23f;

  int status = s21_from_float_to_decimal(f, NULL);

  ck_assert_int_eq(status, 1);
}
END_TEST

#endif