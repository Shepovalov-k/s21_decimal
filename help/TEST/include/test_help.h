#ifndef TEST_HELP_H
#define TEST_HELP_H

#include <check.h>

#include "s21_decimal.h"

int run_help_tests(void);
Suite* abs_suite(void);
Suite* abs_big_suite(void);
Suite* big_add_suite(void);
Suite* big_decimal_to_decimal_suite(void);
Suite* big_get_bit_suite(void);
Suite* big_sub_suite(void);
Suite* decimal_to_big_decimal_suite(void);
Suite* div_by_10_suite(void);
Suite* get_bit_suite(void);
Suite* get_scale_suite(void);
Suite* get_sign_suite(void);
Suite* increase_scale_suite(void);
Suite* increase_scale_big_suite(void);
Suite* is_zero_suite(void);
Suite* is_zero_big_suite(void);
Suite* left_shift_suite(void);
Suite* left_shift_big_suite(void);
Suite* right_shift_big_suite(void);
Suite* mod_by_10_suite(void);
Suite* normalize_big_suite(void);
Suite* normalize_suite(void);
Suite* set_bit_suite(void);
Suite* set_scale_suite(void);
Suite* set_sign_suite(void);

#endif