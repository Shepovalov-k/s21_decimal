#include "test_mod_by_10.h"

#include <check.h>

Suite *mod_by_10_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_mod_by_10\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_mod_by_10_simple);
  tcase_add_test(tc, test_mod_by_10_remainder);
  tcase_add_test(tc, test_mod_by_10_large_number);
  tcase_add_test(tc, test_mod_by_10_multiple_words);
  tcase_add_test(tc, test_mod_by_10_zero);
  tcase_add_test(tc, test_mod_by_10_null_ptr);
  tcase_add_test(tc, test_mod_by_10_max_value);
  tcase_add_test(tc, test_mod_by_10_negative);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_MOD_BY_10
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, mod_by_10_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif