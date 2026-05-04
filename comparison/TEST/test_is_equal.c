#include "test_is_equal.h"

#include <check.h>

Suite *is_equal_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_is_equal\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_zero_equals_zero);
  tcase_add_test(tc, test_positive_integer_equals);
  tcase_add_test(tc, test_int_equals_decimal);
  tcase_add_test(tc, test_different_pos_numbers);
  tcase_add_test(tc, test_neg_equals_pos);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_IS_EQUAL
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, is_equal_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif