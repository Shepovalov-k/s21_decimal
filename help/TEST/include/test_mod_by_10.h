#ifndef TEST_MOD_BY_10_H
#define TEST_MOD_BY_10_H

#include <check.h>

#include "s21_decimal.h"

int s21_mod_by_10(const s21_decimal *value);

START_TEST(test_mod_by_10_simple) {
  s21_decimal value = {{10, 0, 0, 0}};
  int result = s21_mod_by_10(&value);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_mod_by_10_remainder) {
  s21_decimal value = {{123, 0, 0, 0}};
  int result = s21_mod_by_10(&value);
  ck_assert_int_eq(result, 3);  // 123 % 10 = 3
}
END_TEST

START_TEST(test_mod_by_10_large_number) {
  s21_decimal value = {{123456789, 0, 0, 0}};
  int result = s21_mod_by_10(&value);
  ck_assert_int_eq(result, 9);  // 123456789 % 10 = 9
}
END_TEST

START_TEST(test_mod_by_10_multiple_words) {
  s21_decimal value = {{0xFFFFFFFF, 1, 0, 0}};  // 2^32 + 0xFFFFFFFF
  int result = s21_mod_by_10(&value);
  ck_assert_int_eq(result, 1);  // (2^32 + 0xFFFFFFFF) % 10 = 5
}
END_TEST

START_TEST(test_mod_by_10_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  int result = s21_mod_by_10(&value);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_mod_by_10_null_ptr) {
  int result = s21_mod_by_10(NULL);
  ck_assert_int_eq(result, 1);  // Error code
}
END_TEST

START_TEST(test_mod_by_10_max_value) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int result = s21_mod_by_10(&value);
  ck_assert_int_eq(result, 5);  // (2^96-1) % 10 = 5
}
END_TEST

START_TEST(test_mod_by_10_negative) {
  s21_decimal value = {{123, 0, 0, 0x80000000}};  // Negative value
  int result = s21_mod_by_10(&value);
  ck_assert_int_eq(result, 3);  // Should ignore sign
}
END_TEST

#endif