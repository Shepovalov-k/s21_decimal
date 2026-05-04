#include "help.h"

uint32_t s21_big_calculate_last_number(s21_big_decimal d) {
  uint32_t remainder = 0;
  for (int i = 6; i >= 0; --i) {
    uint64_t current = ((uint64_t)remainder << 32) | d.bits[i];
    d.bits[i] = (uint32_t)(current / 10);
    remainder = (uint32_t)(current % 10);
  }
  return remainder;
}