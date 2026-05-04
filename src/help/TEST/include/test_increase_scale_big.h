#ifndef TEST_INCREASE_SCALE_BIG_H
#define TEST_INCREASE_SCALE_BIG_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_increase_scale_basic) {
  s21_big_decimal d = {
      .bits = {1, 0, 0, 0, 0, 0, 0}, .scale_big = 0, .sign_big = 0};
  s21_big_decimal d_expected = {
      .bits = {10, 0, 0, 0, 0, 0, 0}, .scale_big = 1, .sign_big = 0};
  int status = s21_increase_scale_big(&d);
  ck_assert_mem_eq(&d, &d_expected, sizeof(s21_big_decimal));
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_increase_scale_max) {
  s21_big_decimal d = {
      .bits = {1, 0, 0, 0, 0, 0, 0}, .scale_big = 27, .sign_big = 0};
  s21_big_decimal d_expected = {
      .bits = {10, 0, 0, 0, 0, 0, 0}, .scale_big = 28, .sign_big = 0};
  int status = s21_increase_scale_big(&d);

  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&d, &d_expected, sizeof(s21_big_decimal));
}
END_TEST

START_TEST(test_increase_scale_large_number) {
  s21_big_decimal d = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0, 0, 0, 0, 0},
                       .scale_big = 10,
                       .sign_big = 0};

  int status = s21_increase_scale_big(&d);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(d.scale_big, 11);
  // Check that multiplication by 10 was correct
  ck_assert_uint_eq(d.bits[0], 0xFFFFFFF6);
  ck_assert_uint_eq(d.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(d.bits[2], 0x9);
  for (int i = 3; i < 7; i++) {
    ck_assert_uint_eq(d.bits[i], 0);
  }
}
END_TEST

START_TEST(test_increase_scale_overflow) {
  s21_big_decimal d = {
      .bits = {0, 0, 0, 0, 0, 0, 0xfffffff0},  // Nearly max value
      .scale_big = S21_MAX_SCALE - 1,
      .sign_big = 0};

  int status = s21_increase_scale_big(&d);

  ck_assert_int_eq(status, S21_TOO_LARGE);
  ck_assert_int_eq(d.scale_big, S21_MAX_SCALE - 1);
}
END_TEST

START_TEST(test_increase_scale_zero) {
  s21_big_decimal d = {
      .bits = {0, 0, 0, 0, 0, 0, 0}, .scale_big = 5, .sign_big = 0};

  int status = s21_increase_scale_big(&d);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(d.scale_big, 6);
  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(d.bits[i], 0);
  }
}
END_TEST

START_TEST(test_increase_scale_with_carry) {
  s21_big_decimal d = {.bits = {0xCCCCCCCC, 0x33333333, 0, 0, 0, 0, 0},
                       .scale_big = 3,
                       .sign_big = 0};

  int status = s21_increase_scale_big(&d);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(d.scale_big, 4);
  // Verify correct multiplication by 10 with carries
  ck_assert_uint_eq(d.bits[0], 0xFFFFFFF8);
  ck_assert_uint_eq(d.bits[1], 0x00000005);
  ck_assert_uint_eq(d.bits[2], 0x2);
  for (int i = 3; i < 7; i++) {
    ck_assert_uint_eq(d.bits[i], 0);
  }
}
END_TEST

#endif