#ifndef S21_SUB
#define S21_SUB

#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"

START_TEST(test_sub_zero_zero) {
  s21_decimal result;
  s21_decimal zero = {{0, 0, 0, 0}};  // 0

  int status = s21_sub(zero, zero, &result);
  ck_assert_int_eq(status, 0);                      // Expected success
  ck_assert_int_eq(s21_is_equal(result, zero), 1);  // Result should be zero
}
END_TEST

START_TEST(test_sub_pos_five_pos_five) {
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};  // 5 - 5 = 0

  s21_decimal pos_five = {{5, 0, 0, 0}};  // 5

  int status = s21_sub(pos_five, pos_five, &result);
  ck_assert_int_eq(status, 0);                          // Expected success
  ck_assert_int_eq(s21_is_equal(result, expected), 1);  // Result should be 0
}
END_TEST

START_TEST(test_sub_pos_five_pos_ten) {
  s21_decimal result;
  s21_decimal expected = {{5, 0, 0, 0x80000000}};  // 5 - 10 = -5

  s21_decimal pos_five = {{5, 0, 0, 0}};  // 5
  s21_decimal pos_ten = {{10, 0, 0, 0}};  // 10
  int status = s21_sub(pos_five, pos_ten, &result);
  ck_assert_int_eq(status, 0);                          // Expected success
  ck_assert_int_eq(s21_is_equal(result, expected), 1);  // Result should be -5
}
END_TEST

START_TEST(test_sub_neg_five_pos_five) {
  s21_decimal result;
  s21_decimal expected = {{10, 0, 0, 0x80000000}};  // -5 - 5 = -10

  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};  // -5
  s21_decimal pos_five = {{5, 0, 0, 0}};           // 5

  int status = s21_sub(neg_five, pos_five, &result);
  ck_assert_int_eq(status, 0);                          // Expected success
  ck_assert_int_eq(s21_is_equal(result, expected), 1);  // Result should be -10
}
END_TEST

START_TEST(test_sub_max_max) {
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};  // max - max = 0

  s21_decimal max_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // Max value

  int status = s21_sub(max_decimal, max_decimal, &result);
  ck_assert_int_eq(status, 0);                          // Expected success
  ck_assert_int_eq(s21_is_equal(result, expected), 1);  // Result should be 0
}
END_TEST

START_TEST(test_sub_min_min) {
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};  // min - min = 0

  s21_decimal min_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};  // Min value

  int status = s21_sub(min_decimal, min_decimal, &result);
  ck_assert_int_eq(status, 0);                          // Expected success
  ck_assert_int_eq(s21_is_equal(result, expected), 1);  // Result should be 0
}
END_TEST

START_TEST(test_sub_small_numbers) {
  s21_decimal result;
  s21_decimal expected = {
      {0, 0, 0, 0x70000}};  // 0.0000001 - 0.0000001 = 0.0000000

  s21_decimal small_pos = {{1, 0, 0, 0x70000}};  // 0.0000001 (scale 7)

  int status = s21_sub(small_pos, small_pos, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_different_scales) {
  s21_decimal result;
  s21_decimal expected = {{45, 0, 0, 0x10000}};  // 5 - 0.5 = 4.5

  s21_decimal a = {{5, 0, 0, 0}};        // 5
  s21_decimal b = {{5, 0, 0, 0x10000}};  // 0.5

  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_overflow) {
  s21_decimal result;
  s21_decimal max_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // Max value
  s21_decimal min_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};  // Min value

  // max - min would overflow
  int status = s21_sub(max_decimal, min_decimal, &result);
  ck_assert_int_eq(status, 1);  // Expected overflow code
}
END_TEST
// 4,4 -> 4
START_TEST(test_sub_rounding_1) {
  s21_decimal result;
  s21_decimal expected = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{6, 0, 0, 0x10000}};
  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST
// 4,5 -> 4
START_TEST(test_sub_rounding_2) {
  s21_decimal result;
  s21_decimal expected = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{5, 0, 0, 0x10000}};
  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST
// 2,5 -> 2
START_TEST(test_sub_rounding_3) {
  s21_decimal result;
  s21_decimal expected = {{0xFFFFFFFC, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal a = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{5, 0, 0, 0x10000}};
  int status = s21_sub(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

#endif