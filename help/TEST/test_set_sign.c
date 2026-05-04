#include "test_set_sign.h"

#include <check.h>

Suite *set_sign_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_set_sign\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_set_sign_positive);
  tcase_add_test(tc, test_set_sign_negative);
  tcase_add_test(tc, test_set_sign_preserve_scale);
  tcase_add_test(tc, test_set_sign_preserve_value);
  // tcase_add_test(tc, test_set_sign_null_ptr);
  tcase_add_test(tc, test_set_sign_multiple_changes);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_SET_SIGN
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, set_sign_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif