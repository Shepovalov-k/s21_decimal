#ifndef NEGATE_H
#define NEGATE_H
#include <check.h>
#include <limits.h>

#include "s21_decimal.h"

START_TEST(test_negate_basic) {
  s21_decimal value = {{5, 0, 0, 0}};  // positive 5
  s21_decimal result;

  int ret = s21_negate(value, &result);

  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_ne(result.bits[3], value.bits[3]);  // sign should be flipped
}
END_TEST

START_TEST(test_negate_zero) {
  s21_decimal value = {{0, 0, 0, 0}};  // zero
  s21_decimal result;

  int ret = s21_negate(value, &result);

  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_ne(result.bits[3], value.bits[3]);  // sign should be flipped
}
END_TEST

START_TEST(test_negate_negative) {
  s21_decimal value = {{5, 0, 0, 1u << 31}};  // negative 5
  s21_decimal result;

  int ret = s21_negate(value, &result);

  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);  // should be positive now
}
END_TEST

START_TEST(test_negate_null_result) {
  s21_decimal value = {{5, 0, 0, 0}};

  int ret = s21_negate(value, NULL);

  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(test_negate_max_values) {
  s21_decimal value = {{-1, -1, -1, 0}};              // positive max
  s21_decimal expected = {{-1, -1, -1, 2147483648}};  // positive max
  s21_decimal result;

  int ret = s21_negate(value, &result);

  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(value.bits[0], -1);
  ck_assert_int_eq(result.bits[0], -1);
  ck_assert_int_eq(result.bits[1], -1);
  ck_assert_int_eq(result.bits[2], -1);
  ck_assert_mem_eq(result.bits + 3, expected.bits + 3, 4);
}
END_TEST
#endif