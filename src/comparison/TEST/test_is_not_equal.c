#include "test_is_not_equal.h"

#include <check.h>

Suite *is_not_equal_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_is_not_equal\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_not_equal_diff_pos_numbers);
  tcase_add_test(tc, test_not_equal_same_numbers);
  tcase_add_test(tc, test_not_equal_neg_vs_pos);
  tcase_add_test(tc, test_not_equal_zero_vs_small);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_IS_NOT_EQUAL
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, is_not_equal_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif