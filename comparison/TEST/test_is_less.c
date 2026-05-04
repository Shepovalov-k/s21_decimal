#include "test_is_less.h"

#include <check.h>

Suite *is_less_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_is_less\033[0m");
  TCase *tc = tcase_create("Core");

  // Zero comparisons
  tcase_add_test(tc, test_zero_not_less_than_zero);

  // Positive number comparisons
  tcase_add_test(tc, test_smaller_pos_less_than_larger_pos);
  tcase_add_test(tc, test_larger_pos_not_less_than_smaller_pos);

  // Negative number comparisons
  tcase_add_test(tc, test_more_neg_less_than_less_neg);
  tcase_add_test(tc, test_less_neg_not_less_than_more_neg);

  // Mixed sign comparisons
  tcase_add_test(tc, test_neg_less_than_pos);
  tcase_add_test(tc, test_pos_not_less_than_neg);

  // Zero vs non-zero comparisons
  tcase_add_test(tc, test_zero_less_than_pos);
  tcase_add_test(tc, test_zero_not_less_than_neg);
  tcase_add_test(tc, test_pos_not_less_than_zero);
  tcase_add_test(tc, test_neg_less_than_zero);

  // Scale/normalization tests
  tcase_add_test(tc, test_is_less_equal_after_normalization);
  tcase_add_test(tc, test_is_less_different_scales_true);

  // Edge cases
  tcase_add_test(tc, test_is_less_max_less_than_min);
  tcase_add_test(tc, test_is_less_min_less_than_max);
  tcase_add_test(tc, test_is_less_small_pos_less_than_zero);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_IS_LESS
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, is_less_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif