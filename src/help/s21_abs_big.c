#include "help.h"

int s21_abs_big(s21_big_decimal a, s21_big_decimal b) {
  for (int i = 6; i >= 0; --i) {
    if (a.bits[i] > b.bits[i]) return 1;
    if (a.bits[i] < b.bits[i]) return -1;
  }
  return 0;
}