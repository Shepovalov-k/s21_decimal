#include <stdio.h>

#include "s21_decimal.h"

int s21_mod_by_10(const s21_decimal *value) {
  if (value == NULL) {
    return 1;  // ошибка
  }

  unsigned long long remainder = 0;

  for (int i = 95; i >= 0; i--) {
    remainder = (remainder << 1) | s21_get_bit(*value, i);
    if (remainder >= 10) {
      remainder %= 10;
    }
    // Если remainder < 10 — просто продолжаем тянуть его вниз
  }

  return (int)remainder;
}
