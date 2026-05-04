#ifndef TEST_BIG_GET_BIT_H
#define TEST_BIG_GET_BIT_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_get_first_bit) {
  s21_big_decimal d = {
      .bits = {1, 0, 0, 0, 0, 0, 0},  // Only first bit of first word is set
      .scale_big = 0,
      .sign_big = 0};
  ck_assert_int_eq(s21_big_get_bit(d, 0), 1);
  ck_assert_int_eq(s21_big_get_bit(d, 1), 0);
}
END_TEST

START_TEST(test_get_last_bit_of_word) {
  s21_big_decimal d = {
      .bits = {0x80000000, 0, 0, 0, 0, 0, 0},  // Last bit of first word set
      .scale_big = 0,
      .sign_big = 0};
  ck_assert_int_eq(s21_big_get_bit(d, 31), 1);
  ck_assert_int_eq(s21_big_get_bit(d, 30), 0);
}
END_TEST

START_TEST(test_get_middle_bit) {
  s21_big_decimal d = {.bits = {0x00001000, 0, 0, 0, 0, 0, 0},  // Bit 12 set
                       .scale_big = 0,
                       .sign_big = 0};
  ck_assert_int_eq(s21_big_get_bit(d, 12), 1);
  ck_assert_int_eq(s21_big_get_bit(d, 11), 0);
  ck_assert_int_eq(s21_big_get_bit(d, 13), 0);
}
END_TEST

START_TEST(test_get_bit_in_second_word) {
  s21_big_decimal d = {
      .bits = {0, 0x00000001, 0, 0, 0, 0, 0},  // First bit of second word
      .scale_big = 0,
      .sign_big = 0};
  ck_assert_int_eq(s21_big_get_bit(d, 32), 1);
  ck_assert_int_eq(s21_big_get_bit(d, 31), 0);
  ck_assert_int_eq(s21_big_get_bit(d, 33), 0);
}
END_TEST

START_TEST(test_get_bit_in_last_word) {
  s21_big_decimal d = {
      .bits = {0, 0, 0, 0, 0, 0, 0x80000000},  // Last bit of last word
      .scale_big = 0,
      .sign_big = 0};
  ck_assert_int_eq(s21_big_get_bit(d, 223), 1);  // 6 words * 32 + 31 = 223
  ck_assert_int_eq(s21_big_get_bit(d, 222), 0);
}
END_TEST

/*START_TEST(test_get_bit_out_of_range) {
    s21_big_decimal d = {
        .bits = {0, 0, 0, 0, 0, 0, 0},
        .scale_big = 0,
        .sign_big = 0
    };
    // Should return 0 for out of range bits
    ck_assert_int_eq(s21_big_get_bit(d, 224), 0);
    ck_assert_int_eq(s21_big_get_bit(d, -1), 0);
}
END_TEST*/

#endif