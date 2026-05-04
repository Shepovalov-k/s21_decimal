#include "test_is_greater_or_equal.h"

#include <check.h>

Suite *is_greater_or_equal_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_is_greater_or_equal\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_greater_or_equal_equal_values);
  tcase_add_test(tc, test_greater_or_equal_pos_gt_pos);
  tcase_add_test(tc, test_greater_or_equal_pos_lt_pos);
  tcase_add_test(tc, test_greater_or_equal_zero_gt_neg);
  tcase_add_test(tc, test_greater_or_equal_equal_negs);
  tcase_add_test(tc, test_greater_or_equal_neg_gt_neg);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_IS_GREATER_OR_EQUAL
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, is_greater_or_equal_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif