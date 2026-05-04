#ifndef IS_EQUAL_H
#define IS_EQUAL_H

#include <check.h>

#include "s21_decimal.h"

Suite* is_equal_suite(void);

START_TEST(test_zero_equals_zero) {
  s21_decimal zero = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(zero, zero), 1);
}
END_TEST

START_TEST(test_positive_integer_equals) {
  s21_decimal five = {{5, 0, 0, 0}};
  s21_decimal another_five = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(five, another_five), 1);
}
END_TEST

START_TEST(test_int_equals_decimal) {
  s21_decimal five_int = {{5, 0, 0, 0}};
  s21_decimal five_decimal = {{50, 0, 0, 0x00010000}};
  ck_assert_int_eq(s21_is_equal(five_int, five_decimal), 1);
}
END_TEST

START_TEST(test_different_pos_numbers) {
  s21_decimal five = {{5, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(five, ten), 0);
}
END_TEST

START_TEST(test_neg_equals_pos) {
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};
  s21_decimal pos_five = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(neg_five, pos_five), 0);
}
END_TEST

#endif