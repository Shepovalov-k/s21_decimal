#include "help.h"

int s21_big_get_bit(s21_big_decimal d, int index) {
  int word = index / 32;
  int bit = index % 32;
  return (d.bits[word] >> bit) & 1;
}