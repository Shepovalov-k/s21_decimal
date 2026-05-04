#include "help.h"

void s21_set_sign(s21_decimal *d, int sign) {
  if (sign) {
    d->bits[3] |= S21_SIGN_BIT;
  } else {
    d->bits[3] &= ~S21_SIGN_BIT;
  }
}