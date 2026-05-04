#ifndef FLOOR_H
#define FLOOR_H
#include <check.h>
#include <limits.h>

#include "s21_decimal.h"

START_TEST(test_floor_positive) {
  s21_decimal value = {{123456789, 0, 0, 0}};
  s21_set_scale(&value, 5);  // 1234.56789
  s21_decimal result;
  s21_decimal expected = {{1234, 0, 0, 0}};  // 1234 (same as truncate)

  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_floor_positive_no_frac) {
  s21_decimal value = {{123456, 0, 0, 0}};
  s21_set_scale(&value, 0);  // 123456
  s21_decimal result;
  s21_decimal expected = {{123456, 0, 0, 0}};

  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_floor_negative) {
  s21_decimal value = {{123456789, 0, 0, 0}};
  s21_set_scale(&value, 5);  // -1234.56789
  s21_set_sign(&value, 1);
  s21_decimal result;
  s21_decimal expected = {{1235, 0, 0, 0}};
  s21_set_sign(&expected, 1);  // -1235 (floor rounds down)

  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_floor_negative_no_frac) {
  s21_decimal value = {{123456, 0, 0, 0}};
  s21_set_scale(&value, 0);
  s21_set_sign(&value, 1);  // -123456
  s21_decimal result;
  s21_decimal expected = {{123456, 0, 0, 0}};
  s21_set_sign(&expected, 1);

  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_floor_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_set_scale(&value, 5);  // 0.00000
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};

  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_floor_null_result) {
  s21_decimal value = {{123456, 0, 0, 0}};
  int status = s21_floor(value, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

#endif