#include "test_add.h"

#include <check.h>

Suite *add_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_add\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_add_zero_zero);
  tcase_add_test(tc, test_add_pos_five_pos_five);
  tcase_add_test(tc, test_add_pos_five_pos_five_point_zero);
  tcase_add_test(tc, test_add_pos_five_pos_ten);
  tcase_add_test(tc, test_add_neg_five_pos_five);
  tcase_add_test(tc, test_add_max_max);
  tcase_add_test(tc, test_add_min_min);
  tcase_add_test(tc, test_add_small_numbers);
  tcase_add_test(tc, test_add_different_scales);
  tcase_add_test(tc, test_add_with_rounding_1);
  tcase_add_test(tc, test_add_with_rounding_2);
  tcase_add_test(tc, test_add_with_rounding_3);
  tcase_add_test(tc, test_add_with_rounding_4);
  tcase_add_test(tc, test_add_with_rounding_5);
  tcase_add_test(tc, test_add_simple_positive);
  tcase_add_test(tc, test_add_simple_negative);
  tcase_add_test(tc, test_add_negative_plus_positive);
  tcase_add_test(tc, test_add_positive_plus_negative);
  tcase_add_test(tc, test_add_with_carry);
  tcase_add_test(tc, test_add_scale_mismatch);
  tcase_add_test(tc, test_add_with_zero);
  tcase_add_test(tc, test_add_negative_with_zero);
  tcase_add_test(tc, test_add_min_positive);
  tcase_add_test(tc, test_add_fractional);
  tcase_add_test(tc, test_add_overflow_boundary);
  tcase_add_test(tc, test_add_underflow_boundary);
  tcase_add_test(tc, test_add_large_and_small);
  tcase_add_test(tc, test_add_commutative);
  tcase_add_test(tc, test_add_associative);
  tcase_add_test(tc, test_add_opposite);
  tcase_add_test(tc, test_add_two_negative_fractions);
  tcase_add_test(tc, test_add_max_scale_fraction);
  tcase_add_test(tc, test_add_negative_and_positive_with_scale);
  tcase_add_test(tc, test_add_bankers_rounding);
  tcase_add_test(tc, test_add_min_positive_numbers);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_ADD
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, add_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif