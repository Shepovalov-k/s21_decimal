#ifndef ROUND_H
#define ROUND_H
#include <check.h>
#include <limits.h>

#include "s21_decimal.h"

START_TEST(test_round_positive_round_down) {
  s21_decimal value = {{123456, 0, 0, 0}};
  s21_set_scale(&value, 5);  // 1.23456
  s21_decimal result;
  s21_decimal expected = {{1, 0, 0, 0}};  // rounds to 1

  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_round_positive_round_up) {
  s21_decimal value = {{123456, 0, 0, 0}};
  s21_set_scale(&value, 5);  // 1.23456
  value.bits[0] = 123454;    // 1.23454 (last digit 4 < 5)
  s21_decimal result;
  s21_decimal expected = {{1, 0, 0, 0}};  // rounds to 1

  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_round_negative_round_down) {
  s21_decimal value = {{123456, 0, 0, 0}};
  s21_set_scale(&value, 5);
  s21_set_sign(&value, 1);  // -1.23456
  s21_decimal result;
  s21_decimal expected = {{1, 0, 0, 0}};
  s21_set_sign(&expected, 1);  // rounds to -1

  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_round_negative_round_up) {
  s21_decimal value = {{123456, 0, 0, 0}};
  s21_set_scale(&value, 5);
  s21_set_sign(&value, 1);  // -1.23456
  value.bits[0] = 123454;   // -1.23454 (last digit 4 < 5)
  s21_decimal result;
  s21_decimal expected = {{1, 0, 0, 0}};
  s21_set_sign(&expected, 1);  // rounds to -1

  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_round_halfway_up) {
  s21_decimal value = {{123455, 0, 0, 0}};
  s21_set_scale(&value, 5);  // 1.23455 (last digit 5)
  s21_decimal result;
  s21_decimal expected = {{1, 0, 0, 0}};  // rounds to 1

  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_round_halfway_down) {
  s21_decimal value = {{123455, 0, 0, 0}};
  s21_set_scale(&value, 5);
  s21_set_sign(&value, 1);  // -1.23455 (last digit 5)
  s21_decimal result;
  s21_decimal expected = {{1, 0, 0, 0}};
  s21_set_sign(&expected, 1);  // rounds to -1

  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_round_zero_scale) {
  s21_decimal value = {{123456, 0, 0, 0}};
  s21_set_scale(&value, 0);  // 123456
  s21_decimal result;
  s21_decimal expected = {{123456, 0, 0, 0}};

  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_round_null_result) {
  s21_decimal value = {{123456, 0, 0, 0}};
  int status = s21_round(value, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_round_up_to_closest_pos) {
  s21_decimal value = {{123456, 0, 0, 0x10000}};
  s21_decimal result;
  s21_decimal expected = {{12346, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(expected));
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_round_up_to_closest_neg) {
  s21_decimal value = {{123456, 0, 0, 0x80010000}};
  s21_decimal result;
  s21_decimal expected = {{12346, 0, 0, 0x80000000}};
  int status = s21_round(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(expected));
  ck_assert_int_eq(status, 0);
}
END_TEST

#endif