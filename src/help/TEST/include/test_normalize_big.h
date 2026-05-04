#ifndef TEST_NORMALIZE_BIG_H
#define TEST_NORMALIZE_BIG_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_normalize_equal_scales) {
  s21_big_decimal a = {0};
  s21_big_decimal b = {0};

  a.scale_big = 5;

  a.bits[0] = 123;
  b.bits[0] = 456;

  s21_normalize_big(&a, &b);

  ck_assert_int_eq(a.scale_big, 5);
  ck_assert_int_eq(a.scale_big, 5);
  ck_assert_uint_eq(a.bits[0], 123);
  ck_assert_uint_eq(b.bits[0], 45600000);
}
END_TEST

START_TEST(test_normalize_a_smaller_scale) {
  s21_big_decimal a = {.scale_big = 2, .sign_big = 0, .bits = {100, 0, 0, 0}};
  s21_big_decimal b = {.scale_big = 5, .sign_big = 0, .bits = {200, 0, 0, 0}};

  s21_big_decimal a_expected = {
      .scale_big = 5, .sign_big = 0, .bits = {100000, 0, 0, 0}};
  s21_big_decimal b_expected = {
      .scale_big = 5, .sign_big = 0, .bits = {200, 0, 0, 0}};

  s21_normalize_big(&a, &b);

  ck_assert_mem_eq(&a, &a_expected, sizeof(s21_big_decimal));
  ck_assert_mem_eq(&b, &b_expected, sizeof(s21_big_decimal));
}
END_TEST

START_TEST(test_normalize_b_smaller_scale) {
  s21_big_decimal a = {.scale_big = 2, .sign_big = 0, .bits = {100, 0, 0, 0}};
  s21_big_decimal b = {.scale_big = 5, .sign_big = 0, .bits = {200, 0, 0, 0}};

  s21_big_decimal a_expected = {
      .scale_big = 5, .sign_big = 0, .bits = {100000, 0, 0, 0}};
  s21_big_decimal b_expected = {
      .scale_big = 5, .sign_big = 0, .bits = {200, 0, 0, 0}};

  s21_normalize_big(&a, &b);

  ck_assert_mem_eq(&a, &a_expected, sizeof(s21_big_decimal));
  ck_assert_mem_eq(&b, &b_expected, sizeof(s21_big_decimal));
}
END_TEST

START_TEST(test_normalize_zero_a) {
  s21_big_decimal a = {0};
  s21_big_decimal b = {0};
  int scale_a = 2;
  int scale_b = 5;

  b.bits[0] = 200;

  s21_normalize_big(&a, &b);

  ck_assert_int_eq(scale_a, 2);  // Should not change
  ck_assert_int_eq(scale_b, 5);  // Should not change
}
END_TEST

START_TEST(test_normalize_zero_b) {
  s21_big_decimal a = {0};
  s21_big_decimal b = {0};
  int scale_a = 5;
  int scale_b = 2;

  a.bits[0] = 100;

  s21_normalize_big(&a, &b);

  ck_assert_int_eq(scale_a, 5);  // Should not change
  ck_assert_int_eq(scale_b, 2);  // Should not change
}
END_TEST

START_TEST(test_normalize_multiple_steps) {
  s21_big_decimal a = {0};
  s21_big_decimal b = {0};
  b.scale_big = 3;
  a.bits[0] = 100;
  b.bits[0] = 200;

  s21_normalize_big(&a, &b);

  ck_assert_int_eq(a.scale_big, 3);
  ck_assert_int_eq(b.scale_big, 3);
  ck_assert_uint_eq(a.bits[0], 100000);  // 100 * 10^3
  ck_assert_uint_eq(b.bits[0], 200);     // Should remain same
}
END_TEST

#endif