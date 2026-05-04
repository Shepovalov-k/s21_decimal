#include "test_set_bit.h"

#include <check.h>

Suite *set_bit_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_set_bit\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_set_bit_low_word);
  tcase_add_test(tc, test_clear_bit_low_word);
  tcase_add_test(tc, test_set_bit_high_word);
  tcase_add_test(tc, test_clear_bit_high_word);
  tcase_add_test(tc, test_set_bit_boundary);
  tcase_add_test(tc, test_set_bit_out_of_range);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_SET_BIT
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, set_bit_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif