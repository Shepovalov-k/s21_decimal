#ifndef S21_MUL
#define S21_MUL

#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"

START_TEST(test_mul_zero_zero) {
  s21_decimal result;
  s21_decimal zero = {{0, 0, 0, 0}};  // 0

  int status = s21_mul(zero, zero, &result);
  ck_assert_int_eq(status, 0);                      // Expected success
  ck_assert_int_eq(s21_is_equal(result, zero), 1);  // Result should be zero
}
END_TEST

START_TEST(test_mul_pos_five_pos_five) {
  s21_decimal result;
  s21_decimal expected = {{25, 0, 0, 0}};  // 5 * 5 = 25

  s21_decimal pos_five = {{5, 0, 0, 0}};  // 5

  int status = s21_mul(pos_five, pos_five, &result);
  ck_assert_int_eq(status, 0);                          // Expected success
  ck_assert_int_eq(s21_is_equal(result, expected), 1);  // Result should be 25
}
END_TEST

START_TEST(test_mul_pos_five_neg_five) {
  s21_decimal result;
  s21_decimal expected = {{25, 0, 0, 0x80000000}};  // 5 * -5 = -25

  s21_decimal pos_five = {{5, 0, 0, 0}};           // 5
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};  // -5

  int status = s21_mul(pos_five, neg_five, &result);
  ck_assert_int_eq(status, 0);                          // Expected success
  ck_assert_int_eq(s21_is_equal(result, expected), 1);  // Result should be -25
}
END_TEST

START_TEST(test_mul_small_numbers) {
  s21_decimal result;
  s21_decimal expected = {
      {1, 0, 0, 0xE0000}};  // 0.0000001 * 0.0000001 = 0.00000000000001

  s21_decimal small_pos = {{1, 0, 0, 0x70000}};  // 0.0000001 (scale 7)

  int status = s21_mul(small_pos, small_pos, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_different_scales) {
  s21_decimal result;
  s21_decimal expected = {{25, 0, 0, 0x10000}};  // 5.0 * 0.5 = 2.5

  s21_decimal a = {{50, 0, 0, 0x10000}};  // 5.0 (scale 1)
  s21_decimal b = {{5, 0, 0, 0x10000}};   // 0.5 (scale 1)

  int status = s21_mul(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_max_by_one) {
  s21_decimal result;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal max_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // Max value

  int status = s21_mul(max_decimal, one, &result);
  ck_assert_int_eq(status, 0);  // Expected success
  ck_assert_int_eq(s21_is_equal(result, max_decimal),
                   1);  // Result should be max
}
END_TEST

START_TEST(test_mul_max_by_two) {
  s21_decimal result;
  s21_decimal two = {{2, 0, 0, 0}};
  s21_decimal max_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // Max value

  int status = s21_mul(max_decimal, two, &result);
  ck_assert_int_eq(status, 1);  // Expected overflow
}
END_TEST

START_TEST(test_mul_min_by_min) {
  s21_decimal result;
  s21_decimal min_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};  // Min value

  int status = s21_mul(min_decimal, min_decimal, &result);
  ck_assert_int_eq(status,
                   1);  // Expected overflow (min * min would be too large)
}
END_TEST

START_TEST(test_mul_precision_loss) {
  s21_decimal result;
  s21_decimal expected = {
      {123456780, 0, 0, 0x70000}};  // 1.2345678 * 10 = 12.3456780

  s21_decimal a = {{12345678, 0, 0, 0x70000}};  // 1.2345678 (scale 7)
  s21_decimal b = {{10, 0, 0, 0}};              // 10

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_one_by_one_writing_to_null) {
  s21_decimal* result = NULL;
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};

  int status = s21_mul(a, b, result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_mul_one_by_zero) {
  s21_decimal result;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal zero = {{0, 0, 0, 0}};

  int status = s21_mul(one, zero, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, zero), 1);
}
END_TEST

START_TEST(test_mul_min_by_two) {
  s21_decimal result;
  s21_decimal min_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};  // Min value
  s21_decimal two = {{2, 0, 0, 0}};                       // Min value

  int status = s21_mul(min_decimal, two, &result);
  ck_assert_int_eq(status,
                   2);  // Expected overflow (min * min would be too large)
}
END_TEST

#endif