#include "test_truncate.h"

#include <check.h>

Suite *truncate_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[1;34ms21_truncate\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_truncate_positive);
  tcase_add_test(tc_core, test_truncate_negative);
  tcase_add_test(tc_core, test_truncate_zero_scale);
  tcase_add_test(tc_core, test_truncate_max_scale);
  tcase_add_test(tc_core, test_truncate_null_result);
  // tcase_add_test(tc_core, test_truncate_invalid_scale);
  tcase_add_test(tc_core, test_truncate_123p456);

  suite_add_tcase(s, tc_core);

  return s;
}

#ifdef STANDALONE_TRUNCATE
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, truncate_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif