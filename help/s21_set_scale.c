#include "help.h"

void s21_set_scale(s21_decimal *d, int scale) {
  d->bits[3] = (d->bits[3] & (S21_SIGN_BIT | 0xFFFF)) | (scale << 16);
}