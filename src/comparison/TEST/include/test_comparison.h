#ifndef TEST_COMPARISON_H
#define TEST_COMPARISON_H
#include <check.h>

#include "s21_decimal.h"

int run_comparison_tests(void);
Suite* is_equal_suite(void);
Suite* is_not_equal_suite(void);
Suite* is_greater_suite(void);
Suite* is_greater_or_equal_suite(void);
Suite* is_less_suite(void);
Suite* is_less_or_equal_suite(void);

#endif