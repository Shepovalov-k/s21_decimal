#include "test_round.h"

#include <check.h>

Suite *round_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[1;34ms21_round\033[0m");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_round_positive_round_down);
  tcase_add_test(tc_core, test_round_positive_round_up);
  tcase_add_test(tc_core, test_round_negative_round_down);
  tcase_add_test(tc_core, test_round_negative_round_up);
  tcase_add_test(tc_core, test_round_halfway_up);
  tcase_add_test(tc_core, test_round_halfway_down);
  tcase_add_test(tc_core, test_round_zero_scale);
  tcase_add_test(tc_core, test_round_null_result);
  tcase_add_test(tc_core, test_round_up_to_closest_pos);
  tcase_add_test(tc_core, test_round_up_to_closest_neg);

  suite_add_tcase(s, tc_core);

  return s;
}

#ifdef STANDALONE_ROUND
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, round_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif