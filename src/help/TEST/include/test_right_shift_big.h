#ifndef TEST_RIGHT_SHIFT_BIG_H
#define TEST_RIGHT_SHIFT_BIG_H

#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"

START_TEST(test_right_shift_basic) {
  s21_big_decimal num = {0};
  num.bits[0] = 0xFFFFFFFF;  // All bits set

  s21_right_shift_big(&num, 1);
  ck_assert_uint_eq(num.bits[0], 0x7FFFFFFF);
  ck_assert_uint_eq(num.bits[1], 0);
}
END_TEST

START_TEST(test_right_shift_carry) {
  s21_big_decimal num = {0};
  num.bits[1] = 0x80000000;  // MSB set in second word

  s21_right_shift_big(&num, 1);
  ck_assert_uint_eq(num.bits[0], 0x40000000);  // Carry from second word
  ck_assert_uint_eq(num.bits[1], 0x40000000);
}
END_TEST

START_TEST(test_right_shift_multiple_words) {
  s21_big_decimal num = {0};
  num.bits[6] = 0x80000000;  // MSB set in last word

  s21_right_shift_big(&num, 1);
  for (int i = 0; i < 6; i++) {
    ck_assert_uint_eq(num.bits[i], 0);
  }
  ck_assert_uint_eq(num.bits[6], 0x40000000);
}
END_TEST

START_TEST(test_right_shift_zero) {
  s21_big_decimal num = {0};
  num.bits[0] = 0x12345678;

  s21_right_shift_big(&num, 0);  // No shift
  ck_assert_uint_eq(num.bits[0], 0x12345678);
}
END_TEST

START_TEST(test_right_shift_full_word) {
  s21_big_decimal num = {0};
  num.bits[0] = 0xFFFFFFFF;
  num.bits[1] = 0xFFFFFFFF;

  s21_right_shift_big(&num, 32);  // Shift by full word
  ck_assert_uint_eq(num.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(num.bits[1], 0);
}
END_TEST

#endif