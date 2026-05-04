#include "help.h"

void s21_big_sub(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *result) {
  unsigned borrow = 0;
  for (int i = 0; i < 7; ++i) {
    uint64_t diff = (uint64_t)value_1.bits[i] - value_2.bits[i] - borrow;
    result->bits[i] = (uint32_t)(diff & 0xFFFFFFFF);
    borrow = (diff >> 32) & 1;
  }
}