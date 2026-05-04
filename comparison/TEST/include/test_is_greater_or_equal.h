#ifndef IS_GREATER_OR_EQUAL_H
#define IS_GREATER_OR_EQUAL_H

#include <check.h>

#include "s21_decimal.h"

Suite* is_greater_or_equal_suite(void);

START_TEST(test_greater_or_equal_equal_values) {
  s21_decimal five1 = {{5, 0, 0, 0}};
  s21_decimal five2 = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(five1, five2), 1);
}
END_TEST

// Test greater positive numbers (10 >= 5)
START_TEST(test_greater_or_equal_pos_gt_pos) {
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal five = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(ten, five), 1);
}
END_TEST

// Test less positive numbers (5 >= 10)
START_TEST(test_greater_or_equal_pos_lt_pos) {
  s21_decimal five = {{5, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(five, ten), 0);
}
END_TEST

// Test zero vs negative (0 >= -5)
START_TEST(test_greater_or_equal_zero_gt_neg) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(zero, neg_five), 1);
}
END_TEST

// Test equal negative numbers (-5 >= -5)
START_TEST(test_greater_or_equal_equal_negs) {
  s21_decimal neg_five1 = {{5, 0, 0, 0x80000000}};
  s21_decimal neg_five2 = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(neg_five1, neg_five2), 1);
}
END_TEST

// Test greater negative numbers (-5 >= -10)
START_TEST(test_greater_or_equal_neg_gt_neg) {
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};
  s21_decimal neg_ten = {{10, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(neg_five, neg_ten), 1);
}
END_TEST

#endif