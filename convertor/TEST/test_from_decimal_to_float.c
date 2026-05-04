#include "test_from_decimal_to_float.h"

#include <check.h>

Suite* from_decimal_to_float_suite(void) {
  Suite* s = suite_create("\033[1;34ms21_from_decimal_to_float\033[0m");
  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, test_from_decimal_to_float_positive);
  tcase_add_test(tc, test_from_decimal_to_float_negative);
  tcase_add_test(tc, test_from_decimal_to_float_zero);
  tcase_add_test(tc, test_from_decimal_to_float_null);
  tcase_add_test(tc, test_from_decimal_to_float_max);
  tcase_add_test(tc, test_from_decimal_to_float_min);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_FROM_DECIMAL_TO_FLOAT
int main(void) {
  SRunner* sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, from_decimal_to_float_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif