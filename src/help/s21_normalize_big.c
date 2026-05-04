#include "help.h"

void s21_normalize_big(s21_big_decimal *a, s21_big_decimal *b) {
  while (a->scale_big != b->scale_big && !s21_is_zero_big(*a) &&
         !s21_is_zero_big(*b)) {
    if (a->scale_big < b->scale_big) {
      s21_increase_scale_big(a);
    } else {
      s21_increase_scale_big(b);
    }
  }
}