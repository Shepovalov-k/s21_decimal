#ifndef TEST_ARITHMETIC_H
#define TEST_ARITHMETIC_H

#include <check.h>

#include "s21_decimal.h"

int run_arithmetic_tests(void);
Suite* add_suite(void);
Suite* sub_suite(void);
Suite* mul_suite(void);
Suite* div_suite(void);

#endif