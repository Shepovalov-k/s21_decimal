#include "help.h"
// Складывает без учета sign_big (знак учитывается в функции s21_add)
void s21_big_add(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *result) {
  s21_normalize_big(&value_1, &value_2);
  unsigned carry = 0;
  for (int i = 0; i < 7; ++i) {
    uint64_t sum = (uint64_t)value_1.bits[i] + value_2.bits[i] + carry;
    result->bits[i] = (uint32_t)(sum & 0xFFFFFFFF);
    carry = sum >> 32;
  }
  result->scale_big = value_1.scale_big;
  result->sign_big = value_1.sign_big;
}
