#include "help.h"

int s21_big_mul(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal *result) {
  if (!result) return S21_CONVERSION_ERROR;
  s21_big_decimal temp_result = {0};
  int error_status = S21_OK;

  for (int i = 0; i < 7 && !error_status; i++) {
    uint64_t carry = 0;
    for (int j = 0; j < 7 - i && !error_status; j++) {
      uint64_t product = (uint64_t)value_1.bits[i] * value_2.bits[j];
      uint64_t sum =
          (uint64_t)temp_result.bits[i + j] + (product & 0xFFFFFFFF) + carry;

      temp_result.bits[i + j] = (uint32_t)(sum & 0xFFFFFFFF);
      carry = (sum >> 32) + (product >> 32);

      if (i + j + 1 < 7 && carry > 0xFFFFFFFF) {
        error_status = S21_TOO_LARGE;
      }
    }
    // это условие всегда ложно
    if (i + 7 < 7 && carry) {
      temp_result.bits[i + 7] = (uint32_t)carry;
      if (carry > 0xFFFFFFFF) {
        error_status = S21_TOO_LARGE;
      }
    }
  }
  temp_result.scale_big = value_1.scale_big + value_2.scale_big;
  // for (int i = 3; i < 7 && !error_status; i++) {
  //   if (temp_result.bits[i] != 0) {
  //     error_status = S21_TOO_LARGE;
  //   }
  // }

  if (!error_status) {
    *result = temp_result;
    result->sign_big = value_1.sign_big ^ value_2.sign_big;
  } else {
    *result = (s21_big_decimal){0};
  }

  return error_status;
}