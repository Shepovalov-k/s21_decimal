#include "test_arithmetic.h"

#include <check.h>
#include <stdio.h>

int run_arithmetic_tests(void) {
  printf("\033[1;92mTesting of The Arithmetic Functions\033[0m\n");
  SRunner *sr;
  int number_failed = 0;

  sr = srunner_create(add_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(sub_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(mul_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(div_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}

#ifdef STANDALONE_ARITHMETIC
int main(void) { return run_arithmetic_tests(); }
#endif