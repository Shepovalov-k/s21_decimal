#ifndef TEST_SET_SCALE_H
#define TEST_SET_SCALE_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_set_scale_basic) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_set_scale(&result, 5);

  ck_assert_int_eq(s21_get_scale(result), 5);
  ck_assert_int_eq(result.bits[3], 5 << 16);
}
END_TEST

START_TEST(test_set_scale_preserve_sign) {
  s21_decimal result = {{0, 0, 0, 0x80000000}};  // Negative
  s21_decimal expected = {{0, 0, 0, 0x80000000 | (10 << 16)}};

  s21_set_scale(&result, 10);

  ck_assert_int_eq(s21_get_scale(result), 10);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_set_scale_max) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_set_scale(&result, 28);  // Max scale

  ck_assert_int_eq(s21_get_scale(result), 28);
  ck_assert_int_eq(result.bits[3], 28 << 16);
}
END_TEST

START_TEST(test_set_scale_zero) {
  s21_decimal result = {{0, 0, 0, 5 << 16}};  // Existing scale 5
  s21_set_scale(&result, 0);

  ck_assert_int_eq(s21_get_scale(result), 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_set_scale_keep_value_bits) {
  s21_decimal result = {{123, 456, 789, 0x12345678}};
  s21_set_scale(&result, 15);

  ck_assert_int_eq(s21_get_scale(result), 15);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(result.bits[1], 456);
  ck_assert_int_eq(result.bits[2], 789);
  // Only bits 16-23 should change for scale
}
END_TEST

/*START_TEST(test_set_scale_null_ptr) {
  // Should not crash with NULL pointer
  s21_set_scale(NULL, 5);
}
END_TEST*/

#endif