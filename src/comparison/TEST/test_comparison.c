#include "test_comparison.h"

#include <check.h>
#include <stdio.h>

int run_comparison_tests(void) {
  printf("\n");
  printf("\033[1;92mTesting of The Comparison Functions\033[0m\n");
  SRunner *sr;
  int number_failed = 0;

  // Then run just is_less suite
  sr = srunner_create(is_less_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Then run just is_less_or_equal suite
  sr = srunner_create(is_less_or_equal_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Then run just is_greater suite
  sr = srunner_create(is_greater_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Then run just is_greater_or_equal suite
  sr = srunner_create(is_greater_or_equal_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // First run just is_equal suite
  sr = srunner_create(is_equal_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Then run just is_not_equal suite
  sr = srunner_create(is_not_equal_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}

#ifdef STANDALONE_COMPARISON
int main(void) { return run_comparison_tests(); }
#endif