#ifndef TRUNCATE_H
#define TRUNCATE_H
#include <check.h>
#include <limits.h>

#include "s21_decimal.h"

START_TEST(test_truncate_positive) {
  s21_decimal value = {{123456789, 0, 0, 0}};
  s21_set_scale(&value, 5);  // 1234.56789
  s21_decimal result;
  s21_decimal expected = {{1234, 0, 0, 0}};  // 1234 truncated

  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_truncate_negative) {
  s21_decimal value = {{123456789, 0, 0, 0}};
  s21_set_scale(&value, 5);
  s21_set_sign(&value, 1);  // -1234.56789
  s21_decimal result;
  s21_decimal expected = {{1234, 0, 0, 0}};
  s21_set_sign(&expected, 1);  // -1234 truncated

  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_truncate_zero_scale) {
  s21_decimal value = {{123456, 0, 0, 0}};
  s21_set_scale(&value, 0);  // 123456
  s21_decimal result;
  s21_decimal expected = {{123456, 0, 0, 0}};

  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_truncate_max_scale) {
  s21_decimal value = {{1, 0, 0, 0}};
  s21_set_scale(&value, 28);  // 0.0000000000000000000000000001
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};  // 0 after truncate

  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_truncate_null_result) {
  s21_decimal value = {{123456, 0, 0, 0}};
  int status = s21_truncate(value, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

/*START_TEST(test_truncate_invalid_scale) {
  s21_decimal value = {{123456, 0, 0, 0}};
  s21_set_scale(&value, 29);  // Invalid scale
  s21_decimal result;

  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST*/

START_TEST(test_truncate_123p456) {
  s21_decimal value = {{123456, 0, 0, 0}};
  s21_set_scale(&value, 3);  // Invalid scale
  s21_decimal result;
  s21_decimal expected = {{123, 0, 0, 0}};

  int status = s21_truncate(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(expected));
  ck_assert_int_eq(status, 0);
}
END_TEST

#endif