#include "help.h"

int s21_left_shift_big(s21_big_decimal *d, int shift) {
  int error = 0;
  for (int i = 0; i < shift && !error; ++i) {
    uint64_t carry = 0;
    for (int j = 0; j < 7; ++j) {
      uint64_t temp = (uint64_t)d->bits[j] << 1;
      temp |= carry;
      carry = temp >> 32;
      d->bits[j] = (uint32_t)(temp & 0xFFFFFFFF);
    }
    if (carry) error = S21_TOO_LARGE;
  }
  return error;
}