int run_comparison_tests(void);
int run_arithmetic_tests(void);
int run_convertor_tests(void);
int run_other_tests(void);
int run_help_tests(void);

int main(void) {
  return run_comparison_tests() + run_arithmetic_tests() +
         run_convertor_tests() + run_other_tests() + run_help_tests();
}
