#ifndef TEST_OTHER_H
#define TEST_OTHER_H

#include <check.h>

#include "s21_decimal.h"

int run_arithmetic_tests(void);
Suite* floor_suite(void);
Suite* round_suite(void);
Suite* truncate_suite(void);
Suite* negate_suite(void);

#endif