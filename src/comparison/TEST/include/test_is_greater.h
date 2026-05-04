#ifndef IS_GREATER_H
#define IS_GREATER_H

#include <check.h>

#include "s21_decimal.h"

Suite* is_greater_suite(void);

// Test greater with positive numbers (10 > 5)
START_TEST(test_greater_pos_gt_pos) {
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal five = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(ten, five), 1);
}
END_TEST

// Test greater with positive numbers (5 > 10)
START_TEST(test_greater_pos_lt_pos) {
  s21_decimal five = {{5, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(five, ten), 0);
}
END_TEST

// Test greater with negative numbers (-5 > -10)
START_TEST(test_greater_neg_gt_neg) {
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};
  s21_decimal neg_ten = {{10, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(neg_five, neg_ten), 1);
}
END_TEST

// Test greater with mixed signs (5 > -5)
START_TEST(test_greater_pos_gt_neg) {
  s21_decimal pos_five = {{5, 0, 0, 0}};
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(pos_five, neg_five), 1);
}
END_TEST

#endif