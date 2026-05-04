#include "test_left_shift_big.h"

#include <check.h>

Suite *left_shift_big_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_left_shift_big\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_left_shift_basic);
  tcase_add_test(tc, test_left_shift_carry);
  tcase_add_test(tc, test_left_shift_multiple);
  tcase_add_test(tc, test_left_shift_overflow);
  tcase_add_test(tc, test_left_shift_zero);
  tcase_add_test(tc, test_left_shift_full_cascade);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_LEFT_SHIFT_BIG
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, left_shift_big_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif