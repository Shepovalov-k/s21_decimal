#ifndef TEST_BIG_DECIMAL_TO_DECIMAL_H
#define TEST_BIG_DECIMAL_TO_DECIMAL_H

#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "s21_decimal.h"

// Helper functions for testing
static int get_scale(s21_decimal dec) { return (dec.bits[3] >> 16) & 0xFF; }

static int get_sign(s21_decimal dec) { return (dec.bits[3] >> 31) & 1; }

START_TEST(test_valid_conversion) {
  s21_big_decimal src = {.bits = {123456789, 987654321, 555555555, 0, 0, 0, 0},
                         .scale_big = 5,
                         .sign_big = 0};
  s21_decimal dst;
  int scale = 5;
  int sign = 0;

  int ret = s21_big_decimal_to_decimal(&dst, src);

  ck_assert_int_eq(ret, S21_OK);
  ck_assert_int_eq(dst.bits[0], 123456789);
  ck_assert_int_eq(dst.bits[1], 987654321);
  ck_assert_int_eq(dst.bits[2], 555555555);
  // ck_assert_int_eq(dst.bits[3], 0); <- Почему сравнение с нулем?
  ck_assert_int_eq(get_scale(dst), scale);
  ck_assert_int_eq(get_sign(dst), sign);
}
END_TEST

START_TEST(test_overflow_conversion) {
  s21_big_decimal src = {
      .bits = {UINT32_MAX, UINT32_MAX, UINT32_MAX, 1, 0, 0, 0},
      .scale_big = 2,
      .sign_big = 0};
  s21_decimal dst;

  int ret = s21_big_decimal_to_decimal(&dst, src);

  ck_assert_int_eq(ret, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_null_destination) {
  s21_big_decimal src = {
      .bits = {123, 0, 0, 0, 0, 0, 0}, .scale_big = 1, .sign_big = 0};

  int ret = s21_big_decimal_to_decimal(NULL, src);

  ck_assert_int_eq(ret, S21_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_scale_conversion) {
  s21_big_decimal src = {
      .bits = {12345678, 0, 0, 0, 0, 0, 0}, .scale_big = 0, .sign_big = 0};
  s21_decimal dst;

  // Test minimum scale
  int ret = s21_big_decimal_to_decimal(&dst, src);
  ck_assert_int_eq(ret, S21_OK);
  ck_assert_int_eq(get_scale(dst), 0);

  src.scale_big = 28;

  // Test maximum scale
  ret = s21_big_decimal_to_decimal(&dst, src);
  ck_assert_int_eq(ret, S21_OK);
  ck_assert_int_eq(get_scale(dst), 28);
}
END_TEST

START_TEST(test_sign_conversion) {
  s21_big_decimal src = {
      .bits = {42, 0, 0, 0, 0, 0, 0}, .scale_big = 0, .sign_big = 1};
  s21_decimal dst;

  // Test forcing negative sign
  int ret = s21_big_decimal_to_decimal(&dst, src);
  ck_assert_int_eq(ret, S21_OK);
  ck_assert_int_eq(get_sign(dst), 1);

  src.sign_big = 0;

  // Test forcing positive sign
  ret = s21_big_decimal_to_decimal(&dst, src);
  ck_assert_int_eq(ret, S21_OK);
  ck_assert_int_eq(get_sign(dst), 0);
}
END_TEST

START_TEST(test_partial_overflow) {
  s21_big_decimal src = {
      .bits = {123, 456, 789, 1, 0, 0, 0}, .scale_big = 0, .sign_big = 0};
  s21_decimal dst;

  int ret = s21_big_decimal_to_decimal(&dst, src);

  ck_assert_int_eq(ret, S21_TOO_LARGE);
}
END_TEST

#endif