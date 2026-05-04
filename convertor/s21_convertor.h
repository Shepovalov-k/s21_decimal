#ifndef S21_CONVERTOR_H
#define S21_CONVERTOR_H

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "help.h"
#include "s21_decimal.h"

typedef union {
  float f;
  struct parts {
    uint32_t mantissa : FLT_MANT_DIG - 1;
    uint32_t exponent : sizeof(float) * 8 - FLT_MANT_DIG;
    uint32_t sign : 1;
  } parts;
} float_cast;

// Преобразователи
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

#endif