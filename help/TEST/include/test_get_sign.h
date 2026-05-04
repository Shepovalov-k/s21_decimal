#ifndef TEST_GET_SIGN_H
#define TEST_GET_SIGN_H

#include <check.h>
#include <stdlib.h>

#include "s21_decimal.h"

START_TEST(test_get_sign_positive) {
  s21_decimal d = {{0, 0, 0, 0}};  // Clear sign bit (positive)
  int sign = s21_get_sign(d);
  ck_assert_int_eq(sign, 0);
}
END_TEST

START_TEST(test_get_sign_negative) {
  s21_decimal d = {{0, 0, 0, 0x80000000}};  // Set sign bit (negative)
  int sign = s21_get_sign(d);
  ck_assert_int_eq(sign, 1);
}
END_TEST

START_TEST(test_get_sign_with_scale) {
  s21_decimal d = {{0, 0, 0, 0x80010000}};  // Negative with scale 1
  int sign = s21_get_sign(d);
  ck_assert_int_eq(sign, 1);
}
END_TEST

START_TEST(test_get_sign_with_value) {
  s21_decimal d = {{123, 456, 789, 0x80000000}};  // Negative with values
  int sign = s21_get_sign(d);
  ck_assert_int_eq(sign, 1);
}
END_TEST

START_TEST(test_get_sign_random) {
  for (int i = 0; i < 100; i++) {
    s21_decimal d = {{rand(), rand(), rand(), 0}};
    // Test positive
    int sign = s21_get_sign(d);
    ck_assert_int_eq(sign, 0);

    // Test negative
    d.bits[3] |= 0x80000000;
    sign = s21_get_sign(d);
    ck_assert_int_eq(sign, 1);
  }
}
END_TEST

#endif