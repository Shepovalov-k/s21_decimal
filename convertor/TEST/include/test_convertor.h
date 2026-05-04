#ifndef TEST_CONVERTOR_H
#define TEST_CONVERTOR_H
#include <check.h>

#include "s21_decimal.h"

int run_convertor_tests(void);
Suite* from_float_to_decimal_suite(void);
Suite* from_decimal_to_float_suite(void);
Suite* from_decimal_to_int_suite(void);
Suite* from_int_to_decimal_suite(void);

#endif