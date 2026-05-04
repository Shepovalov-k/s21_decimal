#include "test_help.h"

#include <check.h>
#include <stdio.h>

int run_help_tests(void) {
  printf("\033[1;92mTesting of The Help Functions\033[0m\n");
  SRunner *sr;
  int number_failed = 0;

  /*sr = srunner_create(abs_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(abs_big_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);*/

  sr = srunner_create(big_add_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(big_decimal_to_decimal_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(big_get_bit_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(big_sub_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(decimal_to_big_decimal_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(div_by_10_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(get_bit_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(get_scale_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(get_sign_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // sr = srunner_create(increase_scale_suite());
  // srunner_run_all(sr, CK_VERBOSE);
  // number_failed += srunner_ntests_failed(sr);
  // srunner_free(sr);

  sr = srunner_create(increase_scale_big_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(is_zero_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(is_zero_big_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // sr = srunner_create(left_shift_suite());
  // srunner_run_all(sr, CK_VERBOSE);
  // number_failed += srunner_ntests_failed(sr);
  // srunner_free(sr);

  sr = srunner_create(left_shift_big_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(mod_by_10_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // sr = srunner_create(normalize_suite());
  // srunner_run_all(sr, CK_VERBOSE);
  // number_failed += srunner_ntests_failed(sr);
  // srunner_free(sr);

  sr = srunner_create(normalize_big_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(set_bit_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(set_bit_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(set_scale_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(set_sign_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}

#ifdef STANDALONE_HELP
int main(void) { return run_help_tests(); }
#endif
