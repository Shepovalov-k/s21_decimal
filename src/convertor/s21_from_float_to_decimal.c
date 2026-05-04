#include "s21_convertor.h"
#define SIGNIFICANT_DECIMAL_DIGITS 7

void s21_add_one(s21_big_decimal* d) {
  uint64_t carry = 1;
  for (int i = 0; i < 7 && carry; i++) {
    uint64_t sum = (uint64_t)d->bits[i] + carry;
    d->bits[i] = (uint32_t)(sum & 0xFFFFFFFF);
    carry = sum >> 32;
  }
}

void s21_mul_to_2_power_exp(s21_big_decimal* d, int exp) {
  for (int32_t i = 0; i < exp; i++) {
    s21_big_decimal big_two = (s21_big_decimal){0};
    big_two.bits[0] = 2;
    s21_big_mul(*d, big_two, d);
  }
}

void s21_div_to_2_power_exp(s21_big_decimal* d, int exp) {
  for (int32_t i = 0; i < exp; i++) {
    s21_big_decimal big_two = (s21_big_decimal){0};
    big_two.bits[0] = 2;
    s21_normalize_big(d, &big_two);
    s21_big_div(*d, big_two, d);
  }
}

int s21_round_to_max_decimal_digits(s21_big_decimal* d) {
  int error = 0;
  int increase_count = 0;
  int sign = d->sign_big;
  s21_big_decimal copy = *d;
  uint32_t decimal_digit_count = s21_big_calculate_decimal_count(*d);
  int32_t extra_digit_count =
      (int)decimal_digit_count - SIGNIFICANT_DECIMAL_DIGITS;
  for (int32_t i = 0; i < extra_digit_count; i++) {
    copy = *d;
    d->scale_big--;
    s21_decrease_scale_big(d);
  }
  while (d->scale_big < 0) {
    error = s21_increase_scale_big(d);
    increase_count++;
  }
  if (error == 0) {
    uint32_t remainder_copy = s21_big_calculate_last_number(copy);
    if (remainder_copy >= 5) {
      if (increase_count > 0) {
        s21_big_decimal b = {0};
        s21_big_decimal ten = {0};
        b.bits[0] = 1;
        ten.bits[0] = 10;
        for (int i = 0; i < increase_count; i++) s21_big_mul(b, ten, &b);
        s21_big_add(*d, b, d);
      } else
        s21_add_one(d);
    }
  }
  d->sign_big = sign;
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal* dst) {
  int error = 0;

  if (dst == NULL) {
    error = 1;
  } else {
    *dst = (s21_decimal){0};
    if (isnan(src) || isinf(src) ||
        fabsf(src) > 79228162514264337593543950335.0f ||
        (fabsf(src) < 1e-28f && src != 0.0f)) {
      error = 1;
    } else {
      float_cast src_float;
      src_float.f = src;

      int32_t exp = (int32_t)src_float.parts.exponent - 127;
      uint32_t mantissa = src_float.parts.mantissa;

      s21_big_decimal buffer = (s21_big_decimal){0};
      s21_big_decimal big_one = (s21_big_decimal){0};

      buffer.bits[0] = mantissa;
      big_one.bits[0] = 1;
      for (uint32_t i = 0; i < FLT_MANT_DIG - 1; i++) {
        s21_big_decimal big_two = (s21_big_decimal){0};
        big_two.bits[0] = 2;
        s21_normalize_big(&buffer, &big_two);
        s21_big_div(buffer, big_two, &buffer);
      }
      s21_normalize_big(&buffer, &big_one);
      s21_big_add(buffer, big_one, &buffer);
      if (exp > 0) {
        s21_mul_to_2_power_exp(&buffer, exp);
      } else {
        exp = -exp;
        s21_div_to_2_power_exp(&buffer, exp);
      }
      buffer.sign_big = src_float.parts.sign;
      error = s21_round_to_max_decimal_digits(&buffer);
      if (!error) {
        error = s21_is_fit_decimal_range(&buffer);
        if (!error) s21_big_decimal_to_decimal(dst, buffer);
      }
    }
  }
  return error;
}
