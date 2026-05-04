#include "help.h"

int s21_decrease_scale_big(s21_big_decimal *value) {
  unsigned long long remainder = 0;
  unsigned int result[7] = {0};

  // Деление в столбик от старшего бита к младшему
  for (int i = 223; i >= 0; i--) {
    remainder = (remainder << 1) | s21_big_get_bit(*value, i);
    if (remainder >= 10) {
      // ПРАВИЛЬНО: записываем 1, когда можем разделить
      result[i / 32] |= (1U << (i % 32));
      remainder %= 10;  // Вычитаем 10 из остатка
    }
    // Если remainder < 10, в результате остается 0 (уже установлен)
  }
  // Копируем результат обратно
  for (int i = 0; i < 7; i++) {
    value->bits[i] = result[i];
  }
  return 0;
}