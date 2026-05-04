#ifndef TEST_SET_BIT_H
#define TEST_SET_BIT_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_set_bit_low_word) {
  s21_big_decimal d = {0};
  s21_set_bit(&d, 3, 1);              // Set bit 3 in word 0
  ck_assert_uint_eq(d.bits[0], 0x8);  // 1 << 3 = 8
  ck_assert_uint_eq(d.bits[1], 0);
}
END_TEST

START_TEST(test_clear_bit_low_word) {
  s21_big_decimal d = {0};
  d.bits[0] = 0xFFFFFFFF;
  s21_set_bit(&d, 5, 0);                     // Clear bit 5 in word 0
  ck_assert_uint_eq(d.bits[0], 0xFFFFFFDF);  // ~(1 << 5)
}
END_TEST

START_TEST(test_set_bit_high_word) {
  s21_big_decimal d = {0};
  s21_set_bit(&d, 100, 1);             // Set bit 100 (word 3, bit 4)
  ck_assert_uint_eq(d.bits[3], 0x10);  // 1 << 4
  for (int i = 0; i < 7; i++) {
    if (i != 3) ck_assert_uint_eq(d.bits[i], 0);
  }
}
END_TEST

START_TEST(test_clear_bit_high_word) {
  s21_big_decimal d = {0};
  d.bits[6] = 0xFFFFFFFF;
  s21_set_bit(&d, 200, 0);                   // Clear bit 200 (word 6, bit 8)
  ck_assert_uint_eq(d.bits[6], 0xFFFFFEFF);  // ~(1 << 8)
}
END_TEST

START_TEST(test_set_bit_boundary) {
  s21_big_decimal d = {0};
  // Test at word boundaries
  s21_set_bit(&d, 31, 1);  // Last bit of word 0
  s21_set_bit(&d, 32, 1);  // First bit of word 1
  ck_assert_uint_eq(d.bits[0], 0x80000000);
  ck_assert_uint_eq(d.bits[1], 0x1);
}
END_TEST

START_TEST(test_set_bit_out_of_range) {
  s21_big_decimal d = {0};
  // Should safely ignore bits beyond 223 (7 words * 32 bits)
  s21_set_bit(&d, 224, 1);
  for (int i = 0; i < 7; i++) {
    ck_assert_uint_eq(d.bits[i], 0);
  }
}
END_TEST

#endif