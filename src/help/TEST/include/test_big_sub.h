#ifndef TEST_BIG_SUB_H
#define TEST_BIG_SUB_H

#include <check.h>
#include <limits.h>

#include "s21_decimal.h"

START_TEST(test_simple_subtraction) {
  s21_big_decimal value_1 = {
      .bits = {10, 0, 0, 0, 0, 0, 0}, .scale_big = 0, .sign_big = 0};
  s21_big_decimal value_2 = {
      .bits = {3, 0, 0, 0, 0, 0, 0}, .scale_big = 0, .sign_big = 0};
  s21_big_decimal result = {0};

  s21_big_sub(value_1, value_2, &result);

  ck_assert_uint_eq(result.bits[0], 7);
  for (int i = 1; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], 0);
  }
}
END_TEST

START_TEST(test_subtraction_with_borrow) {
  s21_big_decimal value_1 = {.bits = {0, 1, 0, 0, 0, 0, 0},  // 2^32
                             .scale_big = 0,
                             .sign_big = 0};
  s21_big_decimal value_2 = {.bits = {1, 0, 0, 0, 0, 0, 0},  // 1
                             .scale_big = 0,
                             .sign_big = 0};
  s21_big_decimal result = {0};

  s21_big_sub(value_1, value_2, &result);

  ck_assert_uint_eq(result.bits[0], UINT32_MAX);
  ck_assert_uint_eq(result.bits[1], 0);
  for (int i = 2; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], 0);
  }
}
END_TEST

START_TEST(test_large_subtraction) {
  s21_big_decimal value_1 = {
      .bits = {UINT32_MAX, UINT32_MAX, 0, 0, 0, 0, 0},  // 2^64 - 1
      .scale_big = 0,
      .sign_big = 0};
  s21_big_decimal value_2 = {.bits = {1, 0, 0, 0, 0, 0, 0},  // 1
                             .scale_big = 0,
                             .sign_big = 0};
  s21_big_decimal result = {0};

  s21_big_sub(value_1, value_2, &result);

  ck_assert_uint_eq(result.bits[0], UINT32_MAX - 1);
  ck_assert_uint_eq(result.bits[1], UINT32_MAX);
  for (int i = 2; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], 0);
  }
}
END_TEST

START_TEST(test_subtraction_with_multiple_borrows) {
  s21_big_decimal value_1 = {.bits = {0, 0, 1, 0, 0, 0, 0},  // 2^64
                             .scale_big = 0,
                             .sign_big = 0};
  s21_big_decimal value_2 = {.bits = {1, 0, 0, 0, 0, 0, 0},  // 1
                             .scale_big = 0,
                             .sign_big = 0};
  s21_big_decimal result = {0};

  s21_big_sub(value_1, value_2, &result);

  ck_assert_uint_eq(result.bits[0], UINT32_MAX);
  ck_assert_uint_eq(result.bits[1], UINT32_MAX);
  ck_assert_uint_eq(result.bits[2], 0);
  for (int i = 3; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], 0);
  }
}
END_TEST

START_TEST(test_subtraction_result_zero) {
  s21_big_decimal value_1 = {
      .bits = {42, 0, 0, 0, 0, 0, 0}, .scale_big = 0, .sign_big = 0};
  s21_big_decimal value_2 = {
      .bits = {42, 0, 0, 0, 0, 0, 0}, .scale_big = 0, .sign_big = 0};
  s21_big_decimal result = {0};

  s21_big_sub(value_1, value_2, &result);

  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(result.bits[i], 0);
  }
}
END_TEST

START_TEST(test_full_borrow_chain) {
  s21_big_decimal value_1 = {.bits = {0, 0, 0, 0, 0, 0, 1},  // 2^192
                             .scale_big = 0,
                             .sign_big = 0};
  s21_big_decimal value_2 = {.bits = {1, 0, 0, 0, 0, 0, 0},  // 1
                             .scale_big = 0,
                             .sign_big = 0};
  s21_big_decimal result = {0};

  s21_big_sub(value_1, value_2, &result);

  ck_assert_uint_eq(result.bits[0], UINT32_MAX);
  ck_assert_uint_eq(result.bits[1], UINT32_MAX);
  ck_assert_uint_eq(result.bits[2], UINT32_MAX);
  ck_assert_uint_eq(result.bits[3], UINT32_MAX);
  ck_assert_uint_eq(result.bits[4], UINT32_MAX);
  ck_assert_uint_eq(result.bits[5], UINT32_MAX);
  ck_assert_uint_eq(result.bits[6], 0);
}
END_TEST

#endif