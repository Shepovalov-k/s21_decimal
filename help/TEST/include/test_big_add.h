#ifndef TEST_BIG_ADD_H
#define TEST_BIG_ADD_H

#include <check.h>
#include <limits.h>

#include "s21_decimal.h"

START_TEST(test_big_add_same_scale) {
  s21_big_decimal value_1 = {
      .bits = {1, 2, 3, 4, 5, 6, 0}, .scale_big = 2, .sign_big = 0};
  s21_big_decimal value_2 = {
      .bits = {10, 20, 30, 40, 50, 60, 0}, .scale_big = 2, .sign_big = 0};
  s21_big_decimal result = {0};
  s21_big_decimal expected = {
      .bits = {11, 22, 33, 44, 55, 66, 0}, .scale_big = 2, .sign_big = 0};

  s21_big_add(value_1, value_2, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_big_decimal));
}
END_TEST

START_TEST(test_big_add_with_carry) {
  s21_big_decimal value_1 = {
      .bits = {UINT32_MAX, 1, 0, 0, 0, 0, 0}, .scale_big = 0, .sign_big = 0};
  s21_big_decimal value_2 = {
      .bits = {1, 0, 0, 0, 0, 0, 0}, .scale_big = 0, .sign_big = 0};
  s21_big_decimal result = {0};

  s21_big_add(value_1, value_2, &result);

  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[1], 2);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_int_eq(result.scale_big, 0);
  ck_assert_int_eq(result.sign_big, 0);
}
END_TEST

// START_TEST(test_big_add_different_signs) {
//     s21_big_decimal value_1 = {
//         .bits = {100, 0, 0, 0, 0, 0, 0},
//         .scale_big = 1,
//         .sign_big = 0
//     };
//     s21_big_decimal value_2 = {
//         .bits = {50, 0, 0, 0, 0, 0, 0},
//         .scale_big = 1,
//         .sign_big = 1
//     };
//     s21_big_decimal result = {0};

//     s21_big_add(value_1, value_2, &result);

//     ck_assert_uint_eq(result.bits[0], 50);
//     ck_assert_int_eq(result.scale_big, 1);
//     ck_assert_int_eq(result.sign_big, 0);
// }
// END_TEST

// START_TEST(test_big_add_negative_result) {
//     s21_big_decimal value_1 = {
//         .bits = {50, 0, 0, 0, 0, 0, 0},
//         .scale_big = 1,
//         .sign_big = 1
//     };
//     s21_big_decimal value_2 = {
//         .bits = {100, 0, 0, 0, 0, 0, 0},
//         .scale_big = 1,
//         .sign_big = 0
//     };
//     s21_big_decimal result = {0};

//     s21_big_add(value_1, value_2, &result);

//     ck_assert_uint_eq(result.bits[0], 50);
//     ck_assert_int_eq(result.scale_big, 1);
//     ck_assert_int_eq(result.sign_big, 0);
// }
// END_TEST

START_TEST(test_big_add_both_negative) {
  s21_big_decimal value_1 = {
      .bits = {100, 0, 0, 0, 0, 0, 0}, .scale_big = 1, .sign_big = 1};
  s21_big_decimal value_2 = {
      .bits = {50, 0, 0, 0, 0, 0, 0}, .scale_big = 1, .sign_big = 1};
  s21_big_decimal result = {0};

  s21_big_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], 150);
  ck_assert_int_eq(result.scale_big, 1);
  ck_assert_int_eq(result.sign_big, 1);
}
END_TEST

START_TEST(test_big_add_different_scales) {
  s21_big_decimal value_1 = {
      .bits = {100, 0, 0, 0, 0, 0, 0}, .scale_big = 1, .sign_big = 0};
  s21_big_decimal value_2 = {
      .bits = {500, 0, 0, 0, 0, 0, 0}, .scale_big = 2, .sign_big = 0};
  s21_big_decimal result = {0};

  s21_big_add(value_1, value_2, &result);

  ck_assert_uint_eq(result.bits[0], 1500);
  ck_assert_int_eq(result.scale_big, 2);
  ck_assert_int_eq(result.sign_big, 0);
}
END_TEST

#endif