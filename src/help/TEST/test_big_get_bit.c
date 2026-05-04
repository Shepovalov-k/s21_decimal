#include "test_big_get_bit.h"

#include <check.h>

Suite *big_get_bit_suite(void) {
  Suite *s = suite_create("\033[1;34ms21_big_get_bit\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_get_first_bit);
  tcase_add_test(tc, test_get_last_bit_of_word);
  tcase_add_test(tc, test_get_middle_bit);
  tcase_add_test(tc, test_get_bit_in_second_word);
  tcase_add_test(tc, test_get_bit_in_last_word);
  // tcase_add_test(tc, test_get_bit_out_of_range);

  suite_add_tcase(s, tc);
  return s;
}

#ifdef STANDALONE_BIG_GET_BIT
int main(void) {
  SRunner *sr = srunner_create(NULL);
  int number_failed = 0;

  srunner_add_suite(sr, big_get_bit_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif