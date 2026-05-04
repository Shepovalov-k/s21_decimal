#include "help.h"
int s21_increase_scale_big(s21_big_decimal *d) {
  s21_big_decimal temp = *d;
  int error = s21_left_shift_big(&temp, 3);
  if (!error) {
    s21_big_decimal temp2 = *d;
    error = s21_left_shift_big(&temp2, 1);
    if (!error) {
      s21_big_add(temp, temp2, d);
    }
  }
  if (!error && d->scale_big < SCALE_BIG_MAX) {
    (d->scale_big)++;
  } else {
    error = S21_TOO_LARGE;
  }
  return error;
}