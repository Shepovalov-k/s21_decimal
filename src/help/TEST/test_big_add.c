#include "test_big_add.h"

#include <check.h>

Suite *big_add_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_big_add\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_big_add_same_scale);
  tcase_add_test(tc, test_big_add_with_carry);
  // tcase_add_test(tc, test_big_add_different_signs);
  // tcase_add_test(tc, test_big_add_negative_result);
  tcase_add_test(tc, test_big_add_both_negative);
  tcase_add_test(tc, test_big_add_different_scales);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_BIG_ADD
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, big_add_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif