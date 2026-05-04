#ifndef IS_LESS_H
#define IS_LESS_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_zero_not_less_than_zero) {
  s21_decimal zero = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(zero, zero), 0);
}
END_TEST

// Positive number comparisons
START_TEST(test_smaller_pos_less_than_larger_pos) {
  s21_decimal five = {{5, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(five, ten), 1);
}
END_TEST

START_TEST(test_larger_pos_not_less_than_smaller_pos) {
  s21_decimal five = {{5, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(ten, five), 0);
}
END_TEST

// Negative number comparisons
START_TEST(test_more_neg_less_than_less_neg) {
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};
  s21_decimal neg_ten = {{10, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_less(neg_ten, neg_five), 1);
}
END_TEST

START_TEST(test_less_neg_not_less_than_more_neg) {
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};
  s21_decimal neg_ten = {{10, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_less(neg_five, neg_ten), 0);
}
END_TEST

// Mixed sign comparisons
START_TEST(test_neg_less_than_pos) {
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};
  s21_decimal pos_five = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(neg_five, pos_five), 1);
}
END_TEST

START_TEST(test_pos_not_less_than_neg) {
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};
  s21_decimal pos_five = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(pos_five, neg_five), 0);
}
END_TEST

// Zero vs non-zero comparisons
START_TEST(test_zero_less_than_pos) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal five = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(zero, five), 1);
}
END_TEST

START_TEST(test_zero_not_less_than_neg) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_less(zero, neg_five), 0);
}
END_TEST

START_TEST(test_pos_not_less_than_zero) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal five = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(five, zero), 0);
}
END_TEST

START_TEST(test_neg_less_than_zero) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_less(neg_five, zero), 1);
}
END_TEST

START_TEST(test_is_less_equal_after_normalization) {
  s21_decimal pos_five = {{5, 0, 0, 0}};
  s21_decimal pos_five_point_zero = {{50, 0, 0, 0x10000}};
  // 5 < 5.0 should be false (equal after normalization)
  ck_assert_int_eq(s21_is_less(pos_five, pos_five_point_zero), 0);
}
END_TEST

START_TEST(test_is_less_different_scales_true) {
  s21_decimal pos_five_point_zero = {{50, 0, 0, 0x10000}};
  s21_decimal pos_ten = {{10, 0, 0, 0}};  // 10
  // 5.0 < 10 should be true
  ck_assert_int_eq(s21_is_less(pos_five_point_zero, pos_ten), 1);
}
END_TEST

START_TEST(test_is_less_max_less_than_min) {
  s21_decimal max_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // Max value
  s21_decimal min_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};  // Min value
  // Max < Min should be false
  ck_assert_int_eq(s21_is_less(max_decimal, min_decimal), 0);
}
END_TEST

START_TEST(test_is_less_min_less_than_max) {
  s21_decimal max_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // Max value
  s21_decimal min_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};  // Min value

  // Min < Max should be true
  ck_assert_int_eq(s21_is_less(min_decimal, max_decimal), 1);
}
END_TEST

START_TEST(test_is_less_small_pos_less_than_zero) {
  s21_decimal small_pos = {{1, 0, 0, 0x70000}};  // 0.0000001 (scale 7)
  s21_decimal zero = {{0, 0, 0, 0}};             // 0
  // 0.0000001 < 0 should be false
  ck_assert_int_eq(s21_is_less(small_pos, zero), 0);
}
END_TEST

#endif