#ifndef IS_LESS_OR_EQUAL_H
#define IS_LESS_OR_EQUAL_H

#include <check.h>

#include "s21_decimal.h"

Suite* is_less_or_equal(void);

START_TEST(test_is_less_or_equal_equal_values) {
  s21_decimal pos_five = {{5, 0, 0, 0}};       // 5
  s21_decimal pos_five_copy = {{5, 0, 0, 0}};  // 5
  // 5 <= 5 should be true (equal case)
  ck_assert_int_eq(s21_is_less_or_equal(pos_five, pos_five_copy), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_less_than) {
  s21_decimal pos_five = {{5, 0, 0, 0}};  // 5
  s21_decimal pos_ten = {{10, 0, 0, 0}};  // 10
  // 5 <= 10 should be true (less than case)
  ck_assert_int_eq(s21_is_less_or_equal(pos_five, pos_ten), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_greater_than) {
  s21_decimal pos_ten = {{10, 0, 0, 0}};  // 10
  s21_decimal pos_five = {{5, 0, 0, 0}};  // 5
  // 10 <= 5 should be false (greater than case)
  ck_assert_int_eq(s21_is_less_or_equal(pos_ten, pos_five), 0);
}
END_TEST

START_TEST(test_is_less_or_equal_negative_less_than_zero) {
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};  // -5
  s21_decimal zero = {{0, 0, 0, 0}};               // 0
  // -5 <= 0 should be true (negative less than zero)
  ck_assert_int_eq(s21_is_less_or_equal(neg_five, zero), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_different_scales) {
  s21_decimal pos_five = {{5, 0, 0, 0}};                    // 5
  s21_decimal pos_five_point_zero = {{50, 0, 0, 0x10000}};  // 5.0 (scale 1)
  // 5 <= 5.0 should be true (equal after normalization)
  ck_assert_int_eq(s21_is_less_or_equal(pos_five, pos_five_point_zero), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_edge_cases) {
  s21_decimal max_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // Max value
  s21_decimal min_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};  // Min value
  s21_decimal small_pos = {{1, 0, 0, 0x70000}};           // 0.0000001 (scale 7)
  s21_decimal zero = {{0, 0, 0, 0}};                      // 0

  // Max <= Min should be false
  ck_assert_int_eq(s21_is_less_or_equal(max_decimal, min_decimal), 0);
  // Min <= Max should be true
  ck_assert_int_eq(s21_is_less_or_equal(min_decimal, max_decimal), 1);
  // 0.0000001 <= 0 should be false
  ck_assert_int_eq(s21_is_less_or_equal(small_pos, zero), 0);
}
END_TEST

#endif