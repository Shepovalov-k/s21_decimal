#ifndef TEST_LEFT_SHIFT_BIG_H
#define TEST_LEFT_SHIFT_BIG_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_left_shift_basic) {
  s21_big_decimal d = {0};
  d.bits[0] = 0x1;  // 000...0001

  int error = s21_left_shift_big(&d, 1);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(d.bits[0], 0x2);  // Should become 000...0010
}
END_TEST

START_TEST(test_left_shift_carry) {
  s21_big_decimal d = {0};
  d.bits[0] = 0x80000000;  // MSB set

  int error = s21_left_shift_big(&d, 1);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(d.bits[0], 0x0);
  ck_assert_uint_eq(d.bits[1], 0x1);  // Carry to next word
}
END_TEST

START_TEST(test_left_shift_multiple) {
  s21_big_decimal d = {0};
  d.bits[0] = 0x1;

  int error = s21_left_shift_big(&d, 3);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(d.bits[0], 0x8);  // 1 << 3 = 8
}
END_TEST

START_TEST(test_left_shift_overflow) {
  s21_big_decimal d = {0};
  // Fill all bits in the last word
  for (int i = 0; i < 7; i++) {
    d.bits[i] = 0xFFFFFFFF;
  }

  int error = s21_left_shift_big(&d, 1);
  ck_assert_int_eq(error, S21_TOO_LARGE);  // Should overflow
}
END_TEST

START_TEST(test_left_shift_zero) {
  s21_big_decimal d = {0};
  d.bits[0] = 0x5;

  int error = s21_left_shift_big(&d, 0);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(d.bits[0], 0x5);  // Should remain unchanged
}
END_TEST

START_TEST(test_left_shift_full_cascade) {
  s21_big_decimal d = {0};
  d.bits[6] = 0x80000000;  // MSB of last word set

  int error = s21_left_shift_big(&d, 1);
  ck_assert_int_eq(error, S21_TOO_LARGE);  // Should overflow
}
END_TEST

#endif