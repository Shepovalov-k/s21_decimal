#ifndef TEST_SET_SIGN_H
#define TEST_SET_SIGN_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_set_sign_positive) {
  s21_decimal d = {{0, 0, 0, 0x80000000}};  // Start with negative
  s21_set_sign(&d, 0);                      // Set to positive

  ck_assert_int_eq(s21_get_sign(d), 0);
  ck_assert_uint_eq(d.bits[3] & S21_SIGN_BIT, 0);
}
END_TEST

START_TEST(test_set_sign_negative) {
  s21_decimal d = {{0, 0, 0, 0}};  // Start with positive
  s21_set_sign(&d, 1);             // Set to negative

  ck_assert_int_eq(s21_get_sign(d), 1);
  ck_assert_uint_eq(d.bits[3] & S21_SIGN_BIT, S21_SIGN_BIT);
}
END_TEST

START_TEST(test_set_sign_preserve_scale) {
  s21_decimal d = {{0, 0, 0, 0x1C0000}};           // 0 * 10^(-28)
  s21_decimal expected = {{0, 0, 0, 0x801C0000}};  // -0 * 10^(-28)

  s21_set_sign(&d, 1);  // Set to negative

  ck_assert_mem_eq(&d, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_set_sign_preserve_value) {
  s21_decimal d = {{123, 456, 789, 0}};  // Positive with values
  s21_set_sign(&d, 1);                   // Set to negative

  ck_assert_int_eq(s21_get_sign(d), 1);
  ck_assert_int_eq(d.bits[0], 123);
  ck_assert_int_eq(d.bits[1], 456);
  ck_assert_int_eq(d.bits[2], 789);
}
END_TEST

/*START_TEST(test_set_sign_null_ptr) {
  // Should not crash with NULL pointer
  s21_set_sign(NULL, 1);
}
END_TEST*/

START_TEST(test_set_sign_multiple_changes) {
  s21_decimal d = {{0, 0, 0, 0}};

  // Toggle sign multiple times
  s21_set_sign(&d, 1);
  ck_assert_int_eq(s21_get_sign(d), 1);

  s21_set_sign(&d, 0);
  ck_assert_int_eq(s21_get_sign(d), 0);

  s21_set_sign(&d, 1);
  ck_assert_int_eq(s21_get_sign(d), 1);
}
END_TEST

#endif