#include "test_get_scale.h"

#include <check.h>

Suite *get_scale_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_get_scale\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_get_scale_zero);
  tcase_add_test(tc, test_get_scale_min);
  tcase_add_test(tc, test_get_scale_max);
  tcase_add_test(tc, test_get_scale_middle);
  tcase_add_test(tc, test_get_scale_with_sign);
  tcase_add_test(tc, test_get_scale_random);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_GET_SCALE
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, get_scale_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif