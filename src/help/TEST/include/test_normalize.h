#ifndef TEST_NORMALIZE_H
#define TEST_NORMALIZE_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_normalize_equal_scales) {
  s21_decimal a = {{1, 0, 0, 0x00050000}};  // value=1, scale=5
  s21_decimal b = {{2, 0, 0, 0x00050000}};  // value=2, scale=5

  s21_normalize(&a, &b);

  ck_assert_int_eq(s21_get_scale(a), 5);
  ck_assert_int_eq(s21_get_scale(b), 5);
  ck_assert_int_eq(a.bits[0], 1);
  ck_assert_int_eq(b.bits[0], 2);
}
END_TEST

START_TEST(test_normalize_a_smaller_scale) {
  s21_decimal a = {{1, 0, 0, 0x00020000}};  // scale=2
  s21_decimal b = {{2, 0, 0, 0x00050000}};  // scale=5

  s21_normalize(&a, &b);

  ck_assert_int_eq(s21_get_scale(a), 5);
  ck_assert_int_eq(s21_get_scale(b), 5);
  ck_assert_int_eq(a.bits[0], 1000);  // 1 * 10^3
  ck_assert_int_eq(b.bits[0], 2);
}
END_TEST

START_TEST(test_normalize_b_smaller_scale) {
  s21_decimal a = {{1, 0, 0, 0x00050000}};  // scale=5
  s21_decimal b = {{2, 0, 0, 0x00020000}};  // scale=2

  s21_normalize(&a, &b);

  ck_assert_int_eq(s21_get_scale(a), 5);
  ck_assert_int_eq(s21_get_scale(b), 5);
  ck_assert_int_eq(a.bits[0], 1);
  ck_assert_int_eq(b.bits[0], 2000);  // 2 * 10^3
}
END_TEST

START_TEST(test_normalize_max_scale) {
  s21_decimal a = {{1, 0, 0, (S21_MAX_SCALE - 1) << 16}};
  s21_decimal b = {{2, 0, 0, S21_MAX_SCALE << 16}};

  s21_normalize(&a, &b);

  ck_assert_int_eq(s21_get_scale(a), S21_MAX_SCALE);
  ck_assert_int_eq(s21_get_scale(b), S21_MAX_SCALE);
}
END_TEST

START_TEST(test_normalize_zero_a) {
  s21_decimal a = {{0, 0, 0, 0x00020000}};  // zero, scale=2
  s21_decimal b = {{2, 0, 0, 0x00050000}};  // scale=5

  s21_normalize(&a, &b);

  ck_assert_int_eq(s21_get_scale(a), 2);  // Should remain unchanged
  ck_assert_int_eq(s21_get_scale(b), 5);  // Should remain unchanged
}
END_TEST

START_TEST(test_normalize_zero_b) {
  s21_decimal a = {{1, 0, 0, 0x00050000}};  // scale=5
  s21_decimal b = {{0, 0, 0, 0x00020000}};  // zero, scale=2

  s21_normalize(&a, &b);

  ck_assert_int_eq(s21_get_scale(a), 5);  // Should remain unchanged
  ck_assert_int_eq(s21_get_scale(b), 2);  // Should remain unchanged
}
END_TEST

/*START_TEST(test_normalize_null_pointers) {
  s21_decimal a = {{1, 0, 0, 0x00050000}};
  s21_decimal b = {{2, 0, 0, 0x00020000}};

  // Should not crash with NULL pointers
  s21_normalize(NULL, &b);
  s21_normalize(&a, NULL);
  s21_normalize(NULL, NULL);
}
END_TEST*/

#endif