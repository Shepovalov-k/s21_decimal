#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <stdint.h>
typedef struct s21_decimal {
  int bits[4];
} s21_decimal;

typedef struct s21_big_decimal {
  int scale_big;
  int sign_big;
  uint32_t bits[7];
} s21_big_decimal;

#define S21_OK 0
#define S21_TOO_LARGE 1
#define S21_TOO_SMALL 2
#define S21_DIV_BY_ZERO 3
#define S21_CONVERSION_ERROR 1

#define S21_MAX_SCALE 28
#define S21_SIGN_BIT (1U << 31)
#define S21_SCALE_MASK 0x00FF0000
#define S21_SCALE_SHIFT 16

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_get_sign(s21_decimal d);
int s21_get_scale(s21_decimal d);
void s21_set_sign(s21_decimal *d, int sign);
void s21_set_scale(s21_decimal *d, int scale);
int s21_increase_scale(s21_decimal *d);
int s21_left_shift(s21_decimal *d, int shift);
int s21_abs(s21_decimal a, s21_decimal b);
// void s21_normalize(s21_decimal *a, s21_decimal *b);
int s21_is_zero(s21_decimal d);
s21_big_decimal s21_decimal_to_big_decimal(s21_decimal d);
int s21_big_decimal_to_decimal(s21_decimal *dst, s21_big_decimal src);
void s21_big_add(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *result);
void s21_big_sub(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *result);
int s21_abs_big(s21_big_decimal a, s21_big_decimal b);
void s21_normalize_big(s21_big_decimal *a, s21_big_decimal *b);
int s21_is_zero_big(s21_big_decimal d);

int s21_get_bit(s21_decimal d, int index);
int s21_big_get_bit(s21_big_decimal d, int index);

int s21_is_fit_decimal_range(s21_big_decimal *d);
int s21_decrease_scale_big(s21_big_decimal *d);
void s21_set_bit(s21_big_decimal *d, int index, int bit);
int s21_increase_scale_big(s21_big_decimal *d);
int s21_left_shift_big(s21_big_decimal *d, int shift);
void s21_right_shift_big(s21_big_decimal *d, int shift);

#endif  // S21_DECIMAL_H