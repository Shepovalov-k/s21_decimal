#ifndef IS_NOT_EQUAL_H
#define IS_NOT_EQUAL_H

#include <check.h>

#include "s21_decimal.h"

// Test different positive numbers (5 != 10)
START_TEST(test_not_equal_diff_pos_numbers) {
  s21_decimal five = {{5, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(five, ten), 1);
}
END_TEST

// Test identical numbers (5 != 5)
START_TEST(test_not_equal_same_numbers) {
  s21_decimal five1 = {{5, 0, 0, 0}};
  s21_decimal five2 = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(five1, five2), 0);
}
END_TEST

// Test negative vs positive (-5 != 5)
START_TEST(test_not_equal_neg_vs_pos) {
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};  // -5
  s21_decimal pos_five = {{5, 0, 0, 0}};           // +5
  ck_assert_int_eq(s21_is_not_equal(neg_five, pos_five), 1);
}
END_TEST

// Test zero vs small positive (0 != 0.0000001)
START_TEST(test_not_equal_zero_vs_small) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal small_pos = {{1, 0, 0, 0x00070000}};  // 0.0000001
  ck_assert_int_eq(s21_is_not_equal(zero, small_pos), 1);
}
END_TEST

#endif