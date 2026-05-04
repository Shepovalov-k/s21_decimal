#include <stdio.h>

#include "help.h"

void s21_show_decimal(s21_decimal d) {
  printf("Decimal bits:%x.%x.%x.%x\n", d.bits[0], d.bits[1], d.bits[2],
         d.bits[3]);
  printf("Sign:%x\n", s21_get_sign(d));
  printf("Scale:%x\n", s21_get_scale(d));
}