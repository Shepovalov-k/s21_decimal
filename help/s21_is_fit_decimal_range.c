#include <stdio.h>

#include "help.h"

int tail_is_zero(s21_big_decimal *d);

int s21_is_fit_decimal_range(s21_big_decimal *result) {
  int exit_status = 0;
  int scale_error = 0;
  s21_big_decimal copy = {0};
  // подгонка big_decimal к формату decimal
  // в copy в конце подгонки будет храниться число с предпоследней итерации
  // для дальнейшего банковского округления
  while ((!tail_is_zero(result) || result->scale_big > S21_MAX_SCALE) &&
         scale_error == 0) {
    copy = *result;
    result->scale_big--;
    if (result->scale_big >= 0) {
      s21_decrease_scale_big(result);
    } else
      scale_error = 1;
  }

  if (!scale_error) {
    // банковское округление
    // последняя цифра числа на последней итерации подгонки
    uint32_t remainder_rez = s21_big_calculate_last_number(*result);
    // последняя цифра числа на предпоследней итерации подгонки
    uint32_t remainder_copy = s21_big_calculate_last_number(copy);
    // Прибавляем 1, если последняя цифра copy больше 5 (обычное округление)
    // или равно 5, но последняя цифра rez - нечетная.
    if (remainder_copy > 5 ||
        (remainder_copy == 5 && (remainder_rez % 2 != 0))) {
      uint64_t carry = 1;
      for (int i = 0; i < 7 && carry; i++) {
        uint64_t sum = (uint64_t)result->bits[i] + carry;
        result->bits[i] = (uint32_t)(sum & 0xFFFFFFFF);
        carry = sum >> 32;
      }
    }
  }

  if (scale_error || !tail_is_zero(result)) {
    if (result->sign_big == 0)
      exit_status = 1;
    else
      exit_status = 2;
  }

  return exit_status;
}

int tail_is_zero(s21_big_decimal *d) {
  for (int i = 6; i > 2; i--) {
    if (d->bits[i] != 0U) return 0;
  }
  return 1;
}