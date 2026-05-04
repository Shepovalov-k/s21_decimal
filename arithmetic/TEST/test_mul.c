#include "test_mul.h"

#include <check.h>

Suite *mul_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_mul\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_mul_zero_zero);
  tcase_add_test(tc, test_mul_pos_five_pos_five);
  tcase_add_test(tc, test_mul_pos_five_neg_five);
  tcase_add_test(tc, test_mul_small_numbers);
  tcase_add_test(tc, test_mul_different_scales);
  tcase_add_test(tc, test_mul_max_by_one);
  tcase_add_test(tc, test_mul_max_by_two);
  tcase_add_test(tc, test_mul_min_by_min);
  tcase_add_test(tc, test_mul_precision_loss);
  tcase_add_test(tc, test_mul_one_by_one_writing_to_null);
  tcase_add_test(tc, test_mul_one_by_zero);
  tcase_add_test(tc, test_mul_min_by_two);
  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_MUL
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, mul_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif