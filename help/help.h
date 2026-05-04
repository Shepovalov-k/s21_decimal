#ifndef HELP_H
#define HELP_H

#include "s21_decimal.h"

#define SCALE_BIG_MAX 32

int s21_get_sign(s21_decimal d);

int s21_get_scale(s21_decimal d);

void s21_set_sign(s21_decimal *d, int sign);

void s21_set_scale(s21_decimal *d, int scale);

int s21_increase_scale(s21_decimal *d);

int s21_left_shift(s21_decimal *d, int shift);

int s21_abs(s21_decimal a, s21_decimal b);

void s21_normalize(s21_decimal *a, s21_decimal *b);

int s21_is_zero(s21_decimal d);

s21_big_decimal s21_decimal_to_big_decimal(s21_decimal d);

int s21_big_decimal_to_decimal(s21_decimal *dst, s21_big_decimal src);

void s21_big_add(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *result);

void s21_big_sub(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *result);

int s21_big_div(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal *result);

int s21_big_mul(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal *result);

int s21_abs_big(s21_big_decimal a, s21_big_decimal b);

void s21_normalize_big(s21_big_decimal *a, s21_big_decimal *b);

int s21_is_zero_big(s21_big_decimal d);

int s21_get_bit(s21_decimal d, int index);

int s21_big_get_bit(s21_big_decimal d, int index);

void s21_set_bit(s21_big_decimal *d, int index, int bit);

int s21_increase_scale_big(s21_big_decimal *d);

int s21_decrease_scale_big(s21_big_decimal *d);

int s21_is_fit_decimal_range(s21_big_decimal *d);

int s21_left_shift_big(s21_big_decimal *d, int shift);

uint32_t s21_big_calculate_last_number(s21_big_decimal d);

uint32_t s21_big_calculate_decimal_count(s21_big_decimal d);

void s21_show_decimal(s21_decimal d);

void s21_show_big_decimal(s21_big_decimal d);
#endif