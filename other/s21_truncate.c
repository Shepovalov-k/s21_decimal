#include <stdio.h>

#include "other.h"
#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error_code = 0;
  if (result == NULL) {
    error_code = 1;
  } else {
    *result = value;
    int scale = s21_get_scale(value);

    if (scale > 0) {
      for (int i = 0; i < scale; i++) {
        error_code = s21_div_by_10(result);
      }
      s21_set_scale(result, 0);
    }
  }
  return error_code;
}
