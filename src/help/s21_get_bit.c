#include "help.h"

int s21_get_bit(s21_decimal d, int index) {
  int word = index / 32;
  int bit = index % 32;
  return (d.bits[word] >> bit) & 1;
}