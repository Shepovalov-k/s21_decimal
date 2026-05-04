#include "test_from_decimal_to_int.h"

#include <check.h>

Suite* from_decimal_to_int_suite(void) {
  Suite* s = suite_create("\033[1;34ms21_from_decimal_to_int\033[0m");
  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, test_positive_int);
  tcase_add_test(tc, test_negative_int);
  tcase_add_test(tc, test_fractional_part);
  tcase_add_test(tc, test_overflow);
  tcase_add_test(tc, test_high_overflow);
  tcase_add_test(tc, test_middle_overflow);
  tcase_add_test(tc, test_null_pointer);
  tcase_add_test(tc, test_int_max);
  tcase_add_test(tc, test_int_max_plus_one);
  tcase_add_test(tc, test_int_min);
  tcase_add_test(tc, test_int_min_minus_one);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_FROM_DECIMAL_TO_INT
int main(void) {
  SRunner* sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, from_decimal_to_int_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif