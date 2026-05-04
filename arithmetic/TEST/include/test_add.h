#ifndef S21_ADD
#define S21_ADD

#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"

START_TEST(test_add_zero_zero) {
  s21_decimal result;
  s21_decimal zero = {{0, 0, 0, 0}};
  int status = s21_add(zero, zero, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_mem_eq(&result, &zero, sizeof(result));
}
END_TEST

START_TEST(test_add_pos_five_pos_five) {
  s21_decimal result;
  s21_decimal expected = {{10, 0, 0, 0}};
  s21_decimal pos_five = {{5, 0, 0, 0}};
  int status = s21_add(pos_five, pos_five, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_pos_five_pos_five_point_zero) {
  s21_decimal result;
  s21_decimal expected = {{100, 0, 0, 0x10000}};
  s21_decimal pos_five = {{5, 0, 0, 0}};
  s21_decimal pos_five_point_zero = {{50, 0, 0, 0x10000}};
  int status = s21_add(pos_five, pos_five_point_zero, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_pos_five_pos_ten) {
  s21_decimal result;
  s21_decimal pos_five = {{5, 0, 0, 0}};
  s21_decimal pos_ten = {{5, 0, 0, 0}};
  int status = s21_add(pos_five, pos_ten, &result);
  ck_assert_int_eq(status, 0);
  END_TEST
}

START_TEST(test_add_neg_five_pos_five) {
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal neg_five = {{5, 0, 0, 0x80000000}};
  s21_decimal pos_five = {{5, 0, 0, 0}};
  int status = s21_add(neg_five, pos_five, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_max_max) {
  s21_decimal result;
  s21_decimal max_decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_add(max_decimal, max_decimal, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_add_min_min) {
  s21_decimal result;
  s21_decimal min_decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int status = s21_add(min_decimal, min_decimal, &result);
  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(test_add_small_numbers) {
  s21_decimal result;
  s21_decimal expected = {{2, 0, 0, 0x70000}};
  s21_decimal small_pos = {{1, 0, 0, 0x70000}};
  int status = s21_add(small_pos, small_pos, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_different_scales) {
  s21_decimal result;
  s21_decimal expected = {{55, 0, 0, 0x10000}};
  s21_decimal a = {{5, 0, 0, 0x10000}};
  s21_decimal b = {{5, 0, 0, 0}};
  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_with_rounding_1) {
  s21_decimal result;
  s21_decimal expected = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal a = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{5, 0, 0, 0x10000}};
  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_with_rounding_2) {
  s21_decimal result;
  s21_decimal expected = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal a = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{5, 0, 0, 0x10000}};
  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_with_rounding_3) {
  s21_decimal result;
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal a = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{6, 0, 0, 0x10000}};
  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_with_rounding_4) {
  s21_decimal result;
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{4, 0, 0, 0x10000}};
  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_with_rounding_5) {
  s21_decimal result;
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{9, 0, 0, 0x10000}};
  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_add_simple_positive) {
  s21_decimal result, expected = {{15, 0, 0, 0}};
  s21_decimal a = {{10, 0, 0, 0}}, b = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_simple_negative) {
  s21_decimal result, expected = {{15, 0, 0, 0x80000000}};
  s21_decimal a = {{10, 0, 0, 0x80000000}}, b = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_negative_plus_positive) {
  s21_decimal result, expected = {{4, 0, 0, 0x80000000}};
  s21_decimal a = {{7, 0, 0, 0x80000000}}, b = {{3, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_positive_plus_negative) {
  s21_decimal result, expected = {{4, 0, 0, 0}};
  s21_decimal a = {{7, 0, 0, 0}}, b = {{3, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_with_carry) {
  s21_decimal result, expected = {{1000000001, 0, 0, 0}};
  s21_decimal a = {{999999999, 0, 0, 0}}, b = {{2, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_scale_mismatch) {
  s21_decimal result, expected = {{523, 0, 0, 0x20000}};
  s21_decimal a = {{123, 0, 0, 0x20000}}, b = {{4, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_with_zero) {
  s21_decimal result, expected = {{42, 0, 0, 0}};
  s21_decimal a = {{42, 0, 0, 0}}, b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_negative_with_zero) {
  s21_decimal result, expected = {{42, 0, 0, 0x80000000}};
  s21_decimal a = {{42, 0, 0, 0x80000000}}, b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_min_positive) {
  s21_decimal result, expected = {{2, 0, 0, 0x1C0000}};
  s21_decimal a = {{1, 0, 0, 0x1C0000}}, b = {{1, 0, 0, 0x1C0000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_fractional) {
  s21_decimal result, expected = {{12, 0, 0, 0x20000}};
  s21_decimal a = {{1, 0, 0, 0x10000}}, b = {{2, 0, 0, 0x20000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_overflow_boundary) {
  s21_decimal result;
  s21_decimal max_decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_add(max_decimal, one, &result), 1);
}
END_TEST

START_TEST(test_add_underflow_boundary) {
  s21_decimal result;
  s21_decimal min_decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal neg_one = {{1, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_add(min_decimal, neg_one, &result), 2);
}
END_TEST

START_TEST(test_add_large_and_small) {
  s21_decimal result, expected = {{100001, 0, 0, 0x30000}};
  s21_decimal a = {{100, 0, 0, 0}}, b = {{1, 0, 0, 0x30000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_commutative) {
  s21_decimal result1, result2;
  s21_decimal a = {{12345, 0, 0, 0x20000}}, b = {{6789, 0, 0, 0x20000}};
  ck_assert_int_eq(s21_add(a, b, &result1), 0);
  ck_assert_int_eq(s21_add(b, a, &result2), 0);
  ck_assert_int_eq(s21_is_equal(result1, result2), 1);
}
END_TEST

START_TEST(test_add_associative) {
  s21_decimal ab, bc, res1, res2;
  s21_decimal a = {{1, 0, 0, 0}}, b = {{2, 0, 0, 0}}, c = {{3, 0, 0, 0}};
  s21_add(a, b, &ab);
  s21_add(b, c, &bc);
  s21_add(ab, c, &res1);
  s21_add(a, bc, &res2);
  ck_assert_int_eq(s21_is_equal(res1, res2), 1);
}
END_TEST

START_TEST(test_add_opposite) {
  s21_decimal result, expected = {{0, 0, 0, 0}};
  s21_decimal a = {{50, 0, 0, 0x80000000}}, b = {{50, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_two_negative_fractions) {
  s21_decimal result, expected = {{40, 0, 0, 0x10000 | 0x80000000}};
  s21_decimal a = {{15, 0, 0, 0x10000 | 0x80000000}};
  s21_decimal b = {{25, 0, 0, 0x10000 | 0x80000000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_max_scale_fraction) {
  s21_decimal result, expected = {{2, 0, 0, 0x1C0000}};
  s21_decimal a = {{1, 0, 0, 0x1C0000}}, b = {{1, 0, 0, 0x1C0000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_negative_and_positive_with_scale) {
  s21_decimal result, expected = {{25, 0, 0, 0x20000 | 0x80000000}};
  s21_decimal a = {{15, 0, 0, 0x10000 | 0x80000000}};
  s21_decimal b = {{125, 0, 0, 0x20000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_bankers_rounding) {
  s21_decimal result, expected = {{25, 0, 0, 0x10000}};
  s21_decimal a = {{25, 0, 0, 0x10000}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_min_positive_numbers) {
  s21_decimal result, expected = {{2, 0, 0, 0x1C0000}};
  s21_decimal a = {{1, 0, 0, 0x1C0000}};
  s21_decimal b = {{1, 0, 0, 0x1C0000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

#endif