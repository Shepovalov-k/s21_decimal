#ifndef TEST_DIV_BY_10_H
#define TEST_DIV_BY_10_H

#include <check.h>

#include "s21_decimal.h"

int s21_div_by_10(s21_decimal *value);

START_TEST(test_div_by_10_simple) {
  s21_decimal value = {{10, 0, 0, 0}};
  int res = s21_div_by_10(&value);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(value.bits[0], 1);
}
END_TEST

START_TEST(test_div_by_10_large_number) {
  s21_decimal value = {{123456789, 0, 0, 0}};
  int res = s21_div_by_10(&value);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(value.bits[0], 12345678);
}
END_TEST

START_TEST(test_div_by_10_with_remainder) {
  s21_decimal value = {{123612, 0, 0, 0}};
  int res = s21_div_by_10(&value);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(value.bits[0],
                   12361);  // 123 / 10 = 12.3 -> integer part is 12
}
END_TEST

START_TEST(test_div_by_10_multiple_words) {
  s21_decimal result = {{0xC3555555, 0xC5CB155C, 0x2C1D2, 0}};
  s21_decimal expected = {{0xE0555555, 0x13C78222, 0x4695, 0}};
  int status = s21_div_by_10(&result);
  ck_assert_mem_eq(&result, &expected, sizeof(expected));
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_div_by_10_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  int res = s21_div_by_10(&value);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(value.bits[0], 0);
}
END_TEST

START_TEST(test_div_by_10_null_pointer) {
  int res = s21_div_by_10(NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_div_by_10_max_value) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int res = s21_div_by_10(&value);
  ck_assert_int_eq(res, 0);
  // Verify the result is approximately (2^96-1)/10
}
END_TEST

#endif