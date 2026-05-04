#include "test_big_sub.h"

#include <check.h>

Suite *big_sub_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_big_sub\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_simple_subtraction);
  tcase_add_test(tc, test_subtraction_with_borrow);
  tcase_add_test(tc, test_large_subtraction);
  tcase_add_test(tc, test_subtraction_with_multiple_borrows);
  tcase_add_test(tc, test_subtraction_result_zero);
  tcase_add_test(tc, test_full_borrow_chain);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_BIG_SUB
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, big_sub_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif