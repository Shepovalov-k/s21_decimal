#include "test_normalize_big.h"

#include <check.h>

Suite *normalize_big_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_normalize_big\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_normalize_equal_scales);
  tcase_add_test(tc, test_normalize_a_smaller_scale);
  tcase_add_test(tc, test_normalize_b_smaller_scale);
  tcase_add_test(tc, test_normalize_zero_a);
  tcase_add_test(tc, test_normalize_zero_b);
  tcase_add_test(tc, test_normalize_multiple_steps);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_NORMALIZE_BIG
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, normalize_big_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif