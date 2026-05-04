#include "test_big_decimal_to_decimal.h"

#include <check.h>

Suite *big_decimal_to_decimal_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_big_decimal_to_decimal\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_valid_conversion);
  tcase_add_test(tc, test_overflow_conversion);
  tcase_add_test(tc, test_null_destination);
  tcase_add_test(tc, test_scale_conversion);
  tcase_add_test(tc, test_sign_conversion);
  tcase_add_test(tc, test_partial_overflow);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_BIG_DECIMAL_TO_DECIMAL
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, big_decimal_to_decimal_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif