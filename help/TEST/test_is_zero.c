#include "test_is_zero.h"

#include <check.h>

Suite *is_zero_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_is_zero\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_is_zero_zero_dec);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_IS_ZERO
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, is_zero_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif