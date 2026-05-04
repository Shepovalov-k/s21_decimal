#include "help.h"

void s21_set_bit(s21_big_decimal *d, int index, int bit) {
  int word = index / 32;
  int bit_pos = index % 32;
  if (bit) {
    d->bits[word] |= (1U << bit_pos);
  } else {
    d->bits[word] &= ~(1U << bit_pos);
  }
}