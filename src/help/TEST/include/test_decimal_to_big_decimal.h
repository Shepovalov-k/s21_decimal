#ifndef TEST_DECIMAL_TO_BIG_DECIMAL_H
#define TEST_DECIMAL_TO_BIG_DECIMAL_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_conversion_basic) {
  s21_decimal d = {{123, 456, 789, 0}};
  s21_big_decimal result = s21_decimal_to_big_decimal(d);

  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[1], 456);
  ck_assert_uint_eq(result.bits[2], 789);
  for (int i = 3; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], 0);
  }
}
END_TEST

START_TEST(test_conversion_max_values) {
  s21_decimal d = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  s21_big_decimal result = s21_decimal_to_big_decimal(d);

  ck_assert_uint_eq(result.bits[0], UINT32_MAX);
  ck_assert_uint_eq(result.bits[1], UINT32_MAX);
  ck_assert_uint_eq(result.bits[2], UINT32_MAX);
  for (int i = 3; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], 0);
  }
}
END_TEST

START_TEST(test_conversion_zero) {
  s21_decimal d = {{0}};
  s21_big_decimal result = s21_decimal_to_big_decimal(d);

  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], 0);
  }
}
END_TEST

START_TEST(test_conversion_ignores_scale_sign) {
  s21_decimal d = {{123, 0, 0, 0x80010000}};  // Negative, scale = 1
  s21_big_decimal result = s21_decimal_to_big_decimal(d);

  ck_assert_uint_eq(result.bits[0], 123);
  for (int i = 1; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], 0);
  }
}
END_TEST

START_TEST(test_conversion_negative_values) {
  s21_decimal d = {{-123, -456, -789, 0}};
  s21_big_decimal result = s21_decimal_to_big_decimal(d);

  // Testing conversion of negative values (implementation dependent)
  ck_assert_uint_eq(result.bits[0], (uint32_t)-123);
  ck_assert_uint_eq(result.bits[1], (uint32_t)-456);
  ck_assert_uint_eq(result.bits[2], (uint32_t)-789);
  for (int i = 3; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], 0);
  }
}
END_TEST

#endif