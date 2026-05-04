#ifndef TEST_GET_BIT_H
#define TEST_GET_BIT_H

#include <check.h>

#include "s21_decimal.h"

START_TEST(test_get_bit_low_word) {
  s21_decimal d = {{0xAAAAAAAA, 0, 0, 0}};  // 10101010... pattern
  for (int i = 0; i < 32; i++) {
    int expected = (i % 2) ? 1 : 0;
    ck_assert_int_eq(s21_get_bit(d, i), expected);
  }
}
END_TEST

START_TEST(test_get_bit_high_word) {
  s21_decimal d = {{0, 0, 0, 0x55555555}};  // 01010101... pattern
  for (int i = 96; i < 128; i++) {
    int expected = (i % 2) ? 0 : 1;
    ck_assert_int_eq(s21_get_bit(d, i), expected);
  }
}
END_TEST

START_TEST(test_get_bit_middle_word) {
  s21_decimal d = {{0, 0xFFFFFFFF, 0, 0}};  // All bits set
  for (int i = 32; i < 64; i++) {
    ck_assert_int_eq(s21_get_bit(d, i), 1);
  }
}
END_TEST

START_TEST(test_get_bit_zero) {
  s21_decimal d = {{0}};  // All bits zero
  for (int i = 0; i < 128; i++) {
    ck_assert_int_eq(s21_get_bit(d, i), 0);
  }
}
END_TEST

START_TEST(test_get_bit_specific_bits) {
  s21_decimal d = {{
      0x00000001,  // bit 0 set
      0x00010000,  // bit 16 of word 1 set
      0x80000000,  // bit 31 of word 2 set
      0x40000000   // bit 30 of word 3 set
  }};

  // Test specific set bits
  ck_assert_int_eq(s21_get_bit(d, 0), 1);
  ck_assert_int_eq(s21_get_bit(d, 32 + 16), 1);  // word 1, bit 16
  ck_assert_int_eq(s21_get_bit(d, 64 + 31), 1);  // word 2, bit 31
  ck_assert_int_eq(s21_get_bit(d, 96 + 30), 1);  // word 3, bit 30

  // Test some unset bits
  ck_assert_int_eq(s21_get_bit(d, 1), 0);
  ck_assert_int_eq(s21_get_bit(d, 32 + 15), 0);
  ck_assert_int_eq(s21_get_bit(d, 64 + 30), 0);
}
END_TEST

/*START_TEST(test_get_bit_out_of_bounds) {
  s21_decimal d = {{1, 0, 0, 0}};

  // Test negative index
  ck_assert_int_eq(s21_get_bit(d, -1), 0);

  // Test index >= 128
  ck_assert_int_eq(s21_get_bit(d, 128), 0);
  ck_assert_int_eq(s21_get_bit(d, 1000), 0);
}
END_TEST*/

#endif