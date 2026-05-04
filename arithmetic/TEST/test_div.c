#include "test_div.h"

#include <check.h>

Suite *div_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_div\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_div_zero_by_zero);
  tcase_add_test(tc, test_div_by_zero);
  tcase_add_test(tc, test_div_one_by_one);
  tcase_add_test(tc, test_div_pos_five_by_pos_two);
  tcase_add_test(tc, test_div_neg_six_by_pos_three);
  tcase_add_test(tc, test_div_small_numbers);
  tcase_add_test(tc, test_div_different_scales);
  tcase_add_test(tc, test_div_max_by_one);
  tcase_add_test(tc, test_div_one_by_max);
  tcase_add_test(tc, test_div_precision_test);
  tcase_add_test(tc, test_div_zero_by_one);
  tcase_add_test(tc, test_div_one_by_one_writing_to_null);
  tcase_add_test(tc, test_div_max_by_zero_point_one);
  tcase_add_test(tc, test_div_by_two);
  // test_div_by_two

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_DIV
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, div_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif