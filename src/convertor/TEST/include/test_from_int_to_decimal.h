#ifndef TEST_FROM_INT_TO_DECIMAL_H
#define TEST_FROM_INT_TO_DECIMAL_H

#include <check.h>
#include <float.h>
#include <limits.h>
#include <stdlib.h>

#include "s21_decimal.h"

START_TEST(test_positive_int_conversion) {
  s21_decimal result;
  s21_decimal expected = {{12345, 0, 0, 0}};
  int value = 12345;

  int status = s21_from_int_to_decimal(value, &result);

  ck_assert_mem_eq(&result, &expected, sizeof(expected));
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_another_positive_int) {
  s21_decimal dec;
  int num = 67890;

  ck_assert_int_eq(s21_from_int_to_decimal(num, &dec), 0);
  ck_assert_int_eq(dec.bits[0], 67890);
  ck_assert_int_eq(s21_get_sign(dec), 0);
}
END_TEST

START_TEST(test_min_int_conversion) {
  s21_decimal result;
  s21_decimal expected = {{0x80000000, 0, 0, 0x80000000}};
  int num = INT_MIN;

  int status = s21_from_int_to_decimal(num, &result);
  ck_assert_mem_eq(
      &result, &expected,
      sizeof(expected));  // Note: This is the binary representation
  ck_assert_int_eq(s21_get_sign(result), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_null_pointer_conversion) {
  int num = 42;
  ck_assert_int_eq(s21_from_int_to_decimal(num, NULL), 1);
}
END_TEST

#endif