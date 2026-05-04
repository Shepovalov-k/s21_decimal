#include "test_floor.h"

#include <check.h>

Suite *floor_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[1;34ms21_floor\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_floor_positive);
  tcase_add_test(tc_core, test_floor_positive_no_frac);
  tcase_add_test(tc_core, test_floor_negative);
  tcase_add_test(tc_core, test_floor_negative_no_frac);
  tcase_add_test(tc_core, test_floor_zero);
  tcase_add_test(tc_core, test_floor_null_result);

  suite_add_tcase(s, tc_core);

  return s;
}

#ifdef STANDALONE_FLOOR
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, floor_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif