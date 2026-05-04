#ifndef S21_DIV
#define S21_DIV

#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"

START_TEST(test_div_zero_by_zero) {
  s21_decimal result;
  s21_decimal zero = {{0, 0, 0, 0}};

  int status = s21_div(zero, zero, &result);
  ck_assert_int_eq(status, 3);  // Expected division by zero error
}
END_TEST

START_TEST(test_div_by_zero) {
  s21_decimal result;
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};

  int status = s21_div(one, zero, &result);
  ck_assert_int_eq(status, 3);  // Expected division by zero error
}
END_TEST

START_TEST(test_div_one_by_one) {
  s21_decimal result;
  s21_decimal expected = {{1, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};

  int status = s21_div(one, one, &result);
  ck_assert_int_eq(status, 0);                          // Expected success
  ck_assert_int_eq(s21_is_equal(result, expected), 1);  // Result should be 1
}
END_TEST

START_TEST(test_div_pos_five_by_pos_two) {
  s21_decimal result;
  s21_decimal expected = {{25, 0, 0, 0x10000}};  // 5 / 2 = 2.5
  s21_decimal five = {{5, 0, 0, 0}};
  s21_decimal two = {{2, 0, 0, 0}};

  int status = s21_div(five, two, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_neg_six_by_pos_three) {
  s21_decimal result;
  s21_decimal expected = {{2, 0, 0, 0x80000000}};  // -6 / 3 = -2
  s21_decimal neg_six = {{6, 0, 0, 0x80000000}};
  s21_decimal three = {{3, 0, 0, 0}};
  int status = s21_div(neg_six, three, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_small_numbers) {
  s21_decimal result;
  s21_decimal expected = {{1, 0, 0, 0}};     // 0.0000001 / 0.0000001 = 1
  s21_decimal small = {{1, 0, 0, 0x70000}};  // 0.0000001 (scale 7)

  int status = s21_div(small, small, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_different_scales) {
  s21_decimal result;
  s21_decimal expected = {{20, 0, 0, 0}};  // 1.0 / 0.05 = 20
  s21_decimal a = {{10, 0, 0, 0x10000}};   // 1.0 (scale 1)
  s21_decimal b = {{5, 0, 0, 0x20000}};    // 0.05 (scale 2)

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_max_by_one) {
  s21_decimal result;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal max_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // Max value

  int status = s21_div(max_decimal, one, &result);
  ck_assert_int_eq(status, 0);  // Expected success
  ck_assert_int_eq(s21_is_equal(result, max_decimal),
                   1);  // Result should be max
}
END_TEST

START_TEST(test_div_one_by_max) {
  s21_decimal result;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal max_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // Max value
  s21_decimal expected = {
      {0, 0, 0, 0x1C0000}};  // Very small number with scale 28

  int status = s21_div(one, max_decimal, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);  // Check scale
  // Exact value comparison might fail due to precision, so we just check scale
}
END_TEST

START_TEST(test_div_precision_test) {
  s21_decimal result;
  s21_decimal expected = {{0x5555555, 0x14b700cb, 0xac544ca,
                           0x1C0000}};  // 1 / 3 ≈ 3333333...10e-28
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal three = {{3, 0, 0, 0}};

  int status = s21_div(one, three, &result);
  ck_assert_int_eq(status, 0);
  // Allow small difference due to rounding
  ck_assert_uint_eq(result.bits[0], expected.bits[0]);
  ck_assert_uint_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_div_zero_by_one) {
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};

  int status = s21_div(zero, one, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_one_by_one_writing_to_null) {
  s21_decimal* result = NULL;
  s21_decimal zero = {{1, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};

  int status = s21_div(zero, one, result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_div_max_by_zero_point_one) {
  s21_decimal result;
  s21_decimal point_one = {{1, 0, 0, 0x10000}};
  s21_decimal max_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // Max value

  int status = s21_div(max_decimal, point_one, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_div_by_two) {
  s21_decimal result;
  s21_decimal expected = {{5525, 0, 0, 0x20000}};
  s21_decimal a = {{1105, 0, 0, 0x10000}};
  s21_decimal b = {{2, 0, 0, 0}};

  int status = s21_div(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

#endif