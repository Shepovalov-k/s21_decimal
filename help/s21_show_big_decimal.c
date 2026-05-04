#include <stdio.h>
#include <string.h>

#include "help.h"
#define NUMS "0123456789"
#define MAX_LEN 33

int s21_big_int_div_by_10(s21_big_decimal* value, int* rest);

void s21_show_big_decimal(s21_big_decimal d) {
  s21_big_decimal d_tmp = d;
  int last_number = 0;
  char str[] = "0000000000000000000000000000000000";
  if (d.sign_big) str[0] = '-';
  for (int i = MAX_LEN; i >= 0 && !s21_is_zero_big(d); i--) {
    s21_big_int_div_by_10(&d_tmp, &last_number);
    d.scale_big--;
    str[i] = NUMS[last_number];
    if (d.scale_big == 0 && !s21_is_zero_big(d)) {
      i--;
      str[i] = ',';
    }
  }
  printf("Big decimal:%s\n", str);
}

int s21_big_int_div_by_10(s21_big_decimal* value, int* rest) {
  unsigned long long remainder = 0;
  unsigned int result[7] = {0};
  for (int i = 223; i >= 0; i--) {
    remainder = (remainder << 1) | s21_big_get_bit(*value, i);
    if (remainder >= 10) {
      result[i / 32] |= (1U << (i % 32));
      remainder %= 10;
    }
  }
  for (int i = 0; i < 7; i++) {
    value->bits[i] = result[i];
  }
  *rest = remainder;
  return 0;
}