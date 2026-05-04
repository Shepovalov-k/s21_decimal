#include "test_set_scale.h"

#include <check.h>

Suite *set_scale_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_set_scale\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_set_scale_basic);
  tcase_add_test(tc, test_set_scale_preserve_sign);
  tcase_add_test(tc, test_set_scale_max);
  tcase_add_test(tc, test_set_scale_zero);
  tcase_add_test(tc, test_set_scale_keep_value_bits);
  // tcase_add_test(tc, test_set_scale_null_ptr);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_SET_SCALE
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, set_scale_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif