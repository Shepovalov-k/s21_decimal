#ifndef TEST_FROM_DECIMAL_TO_INT_H
#define TEST_FROM_DECIMAL_TO_INT_H

#include <check.h>
#include <float.h>
#include <limits.h>
#include <stdlib.h>

#include "s21_decimal.h"

START_TEST(test_positive_int) {
  s21_decimal dec;
  int num = 123456;
  int res;

  s21_from_int_to_decimal(num, &dec);
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &res), 0);
  ck_assert_int_eq(res, num);
}
END_TEST

START_TEST(test_negative_int) {
  s21_decimal dec;
  int num = -789012;
  int res;

  s21_from_int_to_decimal(num, &dec);
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &res), 0);
  ck_assert_int_eq(res, num);
}
END_TEST

START_TEST(test_fractional_part) {
  s21_decimal value = {{12345, 0, 0, 0}};

  int result;

  s21_set_scale(&value, 2);  // 123.45
  int status = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, 123);  // fractional part should be truncated
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_overflow) {
  s21_decimal dec;
  int res;

  dec.bits[0] = INT_MAX;
  dec.bits[1] = 1;  // > INT_MAX
  ck_assert_int_eq(s21_from_decimal_to_int(dec, &res), 1);
}
END_TEST

START_TEST(test_null_pointer) {
  s21_decimal dec;

  ck_assert_int_eq(s21_from_decimal_to_int(dec, NULL), 1);
}
END_TEST

START_TEST(test_int_max) {
  s21_decimal value = {{0x7FFFFFFF, 0, 0, 0}};
  int result;

  int status = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, INT_MAX);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_int_max_plus_one) {
  s21_decimal value = {{0x80000000, 0, 0, 0}};
  int result;

  int status = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_int_min) {
  s21_decimal value = {{0x80000000, 0, 0, 0x80000000}};
  int result;

  int status = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, INT_MIN);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_int_min_minus_one) {
  s21_decimal value = {{0x80000001, 0, 0, 0x80000000}};
  int result;

  int status = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_middle_overflow) {
  s21_decimal value = {{0, 1, 0, 0}};
  int result;

  int status = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_high_overflow) {
  s21_decimal value = {{0, 0, 1, 0}};
  int result;

  int status = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

#endif