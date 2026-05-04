#ifndef TEST_LEFT_SHIFT_H
#define TEST_LEFT_SHIFT_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_left_shift_single_shift) {
  s21_decimal result = {{1, 0, 0, 0}};
  s21_decimal expected = {{2, 0, 0, 0}};

  int res = s21_left_shift(&result, 1);

  ck_assert_int_eq(res, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_left_shift_multiple_shifts) {
  s21_decimal result = {{1, 0, 0, 0}};
  s21_decimal expected = {{8, 0, 0, 0}};

  int res = s21_left_shift(&result, 3);

  ck_assert_int_eq(res, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_left_shift_carry) {
  s21_decimal result = {{0x80000000, 0, 0, 0}};
  s21_decimal expected = {{0, -1, 0, 0}};  // Very strange

  int res = s21_left_shift(&result, 1);

  ck_assert_int_eq(res, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_left_shift_multiple_carries) {
  s21_decimal result = {{0x80000000, 0x80000000, 0, 0}};
  s21_decimal expected = {{0, -1, -1, 0}};  // Very strange

  int res = s21_left_shift(&result, 1);

  ck_assert_int_eq(res, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_left_shift_overflow) {
  s21_decimal result = {{0, 0, 0xFFFFFFFF, 0}};
  s21_decimal expected = {{0, 0, 0xFFFFFFFF, 0}};

  int res = s21_left_shift(&result, 1);

  ck_assert_int_eq(res, S21_TOO_LARGE);
  ck_assert_mem_eq(&result, &expected,
                   sizeof(s21_decimal));  // Should remain unchanged
}
END_TEST

START_TEST(test_left_shift_zero) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};

  int res = s21_left_shift(&result, 5);

  ck_assert_int_eq(res, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

/*START_TEST(test_left_shift_null_ptr) {
  int res = s21_left_shift(NULL, 1);
  ck_assert_int_eq(res, 1);
}
END_TEST*/

START_TEST(test_left_shift_max_shifts) {
  s21_decimal result = {{1, 0, 0, 0}};
  s21_decimal expected = {{-1, 0, 0, 0}};

  int res = s21_left_shift(&result, 31);

  ck_assert_int_eq(res, 0);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

#endif