#ifndef TEST_GET_SCALE_H
#define TEST_GET_SCALE_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_get_scale_zero) {
  s21_decimal d = {{0, 0, 0, 0}};
  int scale = s21_get_scale(d);
  ck_assert_int_eq(scale, 0);
}
END_TEST

START_TEST(test_get_scale_min) {
  s21_decimal d = {{0, 0, 0, 0}};
  d.bits[3] = 0 << 16;  // Minimum scale (0)
  int scale = s21_get_scale(d);
  ck_assert_int_eq(scale, 0);
}
END_TEST

START_TEST(test_get_scale_max) {
  s21_decimal d = {{0, 0, 0, 0}};
  d.bits[3] = 255 << 16;  // Maximum scale (255)
  int scale = s21_get_scale(d);
  ck_assert_int_eq(scale, 255);
}
END_TEST

START_TEST(test_get_scale_middle) {
  s21_decimal d = {{0, 0, 0, 0}};
  d.bits[3] = 28 << 16;  // Typical max scale (28)
  int scale = s21_get_scale(d);
  ck_assert_int_eq(scale, 28);
}
END_TEST

START_TEST(test_get_scale_with_sign) {
  s21_decimal d = {{0, 0, 0, 0}};
  d.bits[3] = (28 << 16) | 0x80000000;  // Scale 28 with sign bit set
  int scale = s21_get_scale(d);
  ck_assert_int_eq(scale, 28);  // Sign bit shouldn't affect scale
}
END_TEST

START_TEST(test_get_scale_random) {
  for (int i = 0; i <= 255; i++) {
    s21_decimal d = {{0, 0, 0, 0}};
    d.bits[3] = i << 16;
    int scale = s21_get_scale(d);
    ck_assert_int_eq(scale, i);
  }
}
END_TEST

#endif