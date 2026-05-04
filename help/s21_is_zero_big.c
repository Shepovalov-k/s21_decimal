#include "help.h"

int s21_is_zero_big(s21_big_decimal d) {
  for (int i = 0; i < 7; ++i) {
    if (d.bits[i] != 0) return 0;
  }
  return 1;
}