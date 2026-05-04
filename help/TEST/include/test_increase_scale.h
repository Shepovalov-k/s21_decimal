#ifndef TEST_INCREASE_SCALE_H
#define TEST_INCREASE_SCALE_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_increase_scale_basic) {
  s21_decimal d = {{1, 0, 0, 0}};  // value = 1, scale = 0
  int res = s21_increase_scale(&d);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_get_scale(d), 1);
  ck_assert_int_eq(d.bits[0], 10);  // 1 * 10 = 10
}
END_TEST

START_TEST(test_increase_scale_max_scale) {
  s21_decimal d = {{1, 0, 0, S21_MAX_SCALE << 16}};
  int res = s21_increase_scale(&d);

  ck_assert_int_eq(res, S21_TOO_LARGE);
  ck_assert_int_eq(s21_get_scale(d), S21_MAX_SCALE);
}
END_TEST

START_TEST(test_increase_scale_overflow) {
  s21_decimal d = {
      {0x19999999, 0x99999999, 0x19999999, 0}};  // Nearly max value
  int res = s21_increase_scale(&d);

  ck_assert_int_eq(res, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_increase_scale_zero) {
  s21_decimal d = {{0, 0, 0, 5 << 16}};  // value = 0, scale = 5
  int res = s21_increase_scale(&d);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_get_scale(d), 6);
  ck_assert_int_eq(d.bits[0], 0);
}
END_TEST

START_TEST(test_increase_scale_large_number) {
  s21_decimal d = {{123456789, 0, 0, 2 << 16}};  // value = 123456789, scale = 2
  int res = s21_increase_scale(&d);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_get_scale(d), 3);
  ck_assert_int_eq(d.bits[0], 1234567890);  // 123456789 * 10 = 1234567890
}
END_TEST

/*START_TEST(test_increase_scale_null_ptr) {
  int res = s21_increase_scale(NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST*/

#endif