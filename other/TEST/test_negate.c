#include "test_negate.h"

#include <check.h>

Suite *negate_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[1;34ms21_negate\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_negate_basic);
  tcase_add_test(tc_core, test_negate_zero);
  tcase_add_test(tc_core, test_negate_negative);
  tcase_add_test(tc_core, test_negate_null_result);
  tcase_add_test(tc_core, test_negate_max_values);

  suite_add_tcase(s, tc_core);

  return s;
}

#ifdef STANDALONE_NEGATE
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, negate_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif