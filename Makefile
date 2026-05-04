CC := gcc
CFLAGS = -Wall -Wextra -Werror -I.
LDFLAGS :=
LIBRARY := s21_decimal.a

OS = $(shell uname -s)

TEST_COMPARISON_DIR = ./comparison/TEST
TEST_ARITHMETIC_DIR = ./arithmetic/TEST
TEST_CONVERTOR_DIR = ./convertor/TEST
TEST_HELP_DIR = ./help/TEST
TEST_OTHER_DIR = ./other/TEST

OBJ_COMPARISON := ./comparison/comparison.o
OBJ_ARITHMETIC := ./arithmetic/arithmetic.o
OBJ_CONVERTOR  := ./convertor/convertor.o
OBJ_HELP       := ./help/help.o
OBJ_OTHER      := ./other/other.o
OBJ            := $(OBJ_COMPARISON) $(OBJ_ARITHMETIC) $(OBJ_CONVERTOR) $(OBJ_HELP) $(OBJ_OTHER)

TEST_COMPARISON_LIB  := $(TEST_COMPARISON_DIR)/test_comparison.a
TEST_ARITHMETIC_LIB  := $(TEST_ARITHMETIC_DIR)/test_arithmetic.a
TEST_CONVERTOR_LIB   := $(TEST_CONVERTOR_DIR)/test_convertor.a
TEST_OTHER_LIB   := $(TEST_OTHER_DIR)/test_other.a
TEST_HELP_LIB        := $(TEST_HELP_DIR)/test_help.a
TESTS_LIBS           := $(TEST_COMPARISON_LIB) $(TEST_ARITHMETIC_LIB) $(TEST_CONVERTOR_LIB) $(TEST_OTHER_LIB) $(TEST_HELP_LIB) $(TEST_OTHER)

ifeq ($(OS), Darwin)
	CHECK_PATH = /opt/homebrew/opt/check
	CHECK_CFLAGS = -I$(CHECK_PATH)/include
	CHECK_LDFLAGS = -L$(CHECK_PATH)/lib -lcheck -lm -lpthread
else
	CHECK_LDFLAGS = -L$(CHECK_PATH)/lib -lcheck -lm -lpthread -lsubunit
endif

.PHONY: all clean rebuild test gcov_report

all: $(LIBRARY)

$(LIBRARY): s21_decimal.h
$(LIBRARY): $(OBJ)
	ar rcs $(LIBRARY) $(OBJ)

$(OBJ_COMPARISON): $(SRC_COMPARISON)
	$(MAKE) -C ./comparison CFLAGS_EXTERNAL=$(CFLAGS_EXTERNAL)

$(OBJ_CONVERTOR): $(SRC_CONVERTOR)
	$(MAKE) -C ./convertor  CFLAGS_EXTERNAL=$(CFLAGS_EXTERNAL)

$(OBJ_ARITHMETIC): $(SRC_ARITHMETIC)
	$(MAKE) -C ./arithmetic CFLAGS_EXTERNAL=$(CFLAGS_EXTERNAL)

$(OBJ_OTHER):
	$(MAKE) -C ./other CFLAGS_EXTERNAL=$(CFLAGS_EXTERNAL)

$(OBJ_HELP):
	$(MAKE) -C ./help CFLAGS_EXTERNAL=$(CFLAGS_EXTERNAL)


$(TEST_COMPARISON): $(TEST_COMPARISON_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(TEST_COMPARISON_OBJ) -o $(TEST_COMPARISON) $(LIBRARY) $(LDFLAGS)
	$(TEST_COMPARISON)

$(TEST_CONVERTOR): $(TEST_CONVERTOR_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(TEST_CONVERTOR_OBJ) -o $(TEST_CONVERTOR) $(LIBRARY) $(LDFLAGS)
	$(TEST_CONVERTOR)

$(TEST_HELP): $(TEST_HELP_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(TEST_HELP_OBJ) -o $(TEST_HELP) $(LIBRARY) $(LDFLAGS)
	$(TEST_HELP)
test: $(LIBRARY)
	$(MAKE) -C $(TEST_COMPARISON_DIR) test_comparison.a CFLAGS_EXTERNAL=$(CFLAGS_EXTERNAL)
	$(MAKE) -C $(TEST_ARITHMETIC_DIR) test_arithmetic.a CFLAGS_EXTERNAL=$(CFLAGS_EXTERNAL)
	$(MAKE) -C $(TEST_CONVERTOR_DIR) test_convertor.a   CFLAGS_EXTERNAL=$(CFLAGS_EXTERNAL)
	$(MAKE) -C $(TEST_OTHER_DIR) test_other.a   CFLAGS_EXTERNAL=$(CFLAGS_EXTERNAL)
	$(MAKE) -C $(TEST_HELP_DIR) test_help.a             CFLAGS_EXTERNAL=$(CFLAGS_EXTERNAL)
	$(CC) $(CFLAGS) -o test ./test_s21_decimal.c $(TESTS_LIBS) $(LIBRARY) $(LDFLAGS) $(CHECK_LDFLAGS) $(LDFLAGS_EXTERNAL)
	./test

gcov_report: CFLAGS_EXTERNAL=--coverage
gcov_report: LDFLAGS_EXTERNAL=-lgcov
gcov_report: clean test
	mkdir -p gcov_report
	rm -f test*.g*
	rm -f ./comparison/TEST/test*.g*
	rm -f ./arithmetic/TEST/test*.g*
	rm -f ./convertor/TEST/test*.g*
	rm -f ./help/TEST/test*.g*
	rm -f ./help/s21*.g*
	rm -f ./other/TEST/test*.g*
	gcovr --html --html-details -o gcov_report/index.html

clean:
	rm -rf $(LIBRARY) test *.o *.gno ./gcov_report
	$(MAKE) -C ./comparison clean
	$(MAKE) -C ./arithmetic clean
	$(MAKE) -C ./convertor clean
	$(MAKE) -C ./other clean
	$(MAKE) -C ./help clean
	$(MAKE) -C ./comparison/TEST clean
	$(MAKE) -C ./arithmetic/TEST clean
	$(MAKE) -C ./convertor/TEST clean
	$(MAKE) -C ./other/TEST clean
	$(MAKE) -C ./help/TEST clean