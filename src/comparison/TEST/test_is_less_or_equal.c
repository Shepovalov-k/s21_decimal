#include "test_is_less_or_equal.h"

#include <check.h>

Suite *is_less_or_equal_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_is_less_or_equal\033[0m");
  TCase *tc = tcase_create("Core");

  // Add all test cases from the header file
  tcase_add_test(tc, test_is_less_or_equal_equal_values);
  tcase_add_test(tc, test_is_less_or_equal_less_than);
  tcase_add_test(tc, test_is_less_or_equal_greater_than);
  tcase_add_test(tc, test_is_less_or_equal_negative_less_than_zero);
  tcase_add_test(tc, test_is_less_or_equal_different_scales);
  tcase_add_test(tc, test_is_less_or_equal_edge_cases);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_IS_LESS_OR_EQUAL
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, is_less_or_equal_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif