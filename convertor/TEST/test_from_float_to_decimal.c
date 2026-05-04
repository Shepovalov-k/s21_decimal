#include "test_from_float_to_decimal.h"

#include <check.h>

Suite* from_float_to_decimal_suite(void) {
  Suite* s = suite_create("\033[1;34ms21_from_float_to_decimal\033[0m");
  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, test_positive_float_conversion);
  tcase_add_test(tc, test_negative_float_conversion);
  tcase_add_test(tc, test_big_digit_count_float_conversion);
  tcase_add_test(tc, test_zero_conversion);
  tcase_add_test(tc, test_small_number_conversion);
  tcase_add_test(tc, test_large_number_conversion);
  tcase_add_test(tc, test_nan_conversion);
  tcase_add_test(tc, test_inf_conversion);
  tcase_add_test(tc, test_null_pointer_conversion);
  tcase_add_test(tc, test_big_digit_count_float_int_conversion);
  tcase_add_test(tc, test_big_digit_count_float_negative_exp_conversion);
  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_FROM_FLOAT_TO_DECIMAL
int main(void) {
  SRunner* sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, from_float_to_decimal_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif