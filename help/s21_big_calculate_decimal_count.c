#include "help.h"

uint32_t s21_big_calculate_decimal_count(s21_big_decimal d) {
  uint32_t result = 0;
  while (!s21_is_zero_big(d)) {
    // делим мантиссу на 10
    s21_decrease_scale_big(&d);
    result++;
  }
  return result;
}