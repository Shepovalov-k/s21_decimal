#include "other.h"
#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;

  int sign = s21_get_sign(value);
  int scale = s21_get_scale(value);
  *result = value;

  if (scale > 0) {
    // Создаем копию и делим на 10 (scale - 1) раз, чтобы добраться до последней
    // дробной цифры
    s21_decimal copy = value;
    for (int i = 0; i < scale - 1; ++i) s21_div_by_10(&copy);

    // Получаем последнюю дробную цифру
    int last_digit = s21_mod_by_10(&copy);

    // Убираем дробную часть
    s21_truncate(value, result);

    // Если >= 5 — округляем
    if (last_digit >= 5) {
      s21_decimal one = {{1, 0, 0, 0}};
      if (!sign) {
        s21_add(*result, one, result);
      } else {
        s21_sub(*result, one, result);
      }
    }
  }

  return 0;
}
