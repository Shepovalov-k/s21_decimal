#include "test_convertor.h"

#include <stdio.h>

int run_convertor_tests(void) {
  printf("\033[1;92mTesting of The Convertor Functions\033[0m\n");
  SRunner *sr;
  int number_failed = 0;

  sr = srunner_create(from_int_to_decimal_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(from_float_to_decimal_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(from_decimal_to_int_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(from_decimal_to_float_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#ifdef STANDALONE_CONVERTOR
int main(void) { return run_convertor_tests(); }
#endif