#include "test_sub.h"

#include <check.h>

Suite *sub_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_sub\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_sub_zero_zero);
  tcase_add_test(tc, test_sub_pos_five_pos_five);
  tcase_add_test(tc, test_sub_pos_five_pos_ten);
  tcase_add_test(tc, test_sub_neg_five_pos_five);
  tcase_add_test(tc, test_sub_max_max);
  tcase_add_test(tc, test_sub_min_min);
  tcase_add_test(tc, test_sub_small_numbers);
  tcase_add_test(tc, test_sub_different_scales);
  tcase_add_test(tc, test_sub_overflow);
  tcase_add_test(tc, test_sub_rounding_1);
  tcase_add_test(tc, test_sub_rounding_2);
  tcase_add_test(tc, test_sub_rounding_3);
  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_SUB
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, sub_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif