#include <stdio.h>

#include "s21_decimal.h"

int s21_div_by_10(s21_decimal *value) {
  if (value == NULL) {
    return 1;
  }

  unsigned long long remainder = 0;
  unsigned int result[3] = {0};

  // Деление в столбик от старшего бита к младшему
  for (int i = 95; i >= 0; i--) {
    remainder = (remainder << 1) | s21_get_bit(*value, i);
    if (remainder >= 10) {
      // ПРАВИЛЬНО: записываем 1, когда можем разделить
      result[i / 32] |= (1U << (i % 32));
      remainder %= 10;  // Вычитаем 10 из остатка
    }
    // Если remainder < 10, в результате остается 0 (уже установлен)
  }
  // Копируем результат обратно
  value->bits[0] = result[0];
  value->bits[1] = result[1];
  value->bits[2] = result[2];

  return 0;
}
