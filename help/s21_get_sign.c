#include "help.h"

int s21_get_sign(s21_decimal d) { return (d.bits[3] >> 31) & 1; }
