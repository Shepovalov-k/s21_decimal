#include "test_other.h"

#include <check.h>
#include <stdio.h>

int run_other_tests(void) {
  printf("\033[1;92mTesting of The Other Functions\033[0m\n");
  SRunner *sr;
  int number_failed = 0;

  sr = srunner_create(floor_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(round_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(truncate_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(negate_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}

#ifdef STANDALONE_OTHER
int main(void) { return run_other_tests(); }
#endif