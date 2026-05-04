CC := gcc
CFLAGS = -Wall -Wextra -Werror -I./include -I../../

OS = $(shell uname -s)

LIBRARY := ../../s21_decimal.a

TEST_SRC_HELP := $(wildcard *.c)
TEST_OBJ_HELP := $(TEST_SRC_HELP:.c=.o)

TEST_HELP_LIB := test_help.a

$(TEST_HELP_LIB): $(TEST_OBJ_HELP)
	ar rcs $(TEST_HELP_LIB) $(TEST_OBJ_HELP)

$(LIBRARY):
	$(MAKE) -C ../.. $(notdir $(LIBRARY))

all: test_help

%.o: %.h
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

test_is_zero: CFLAGS += -DSTANDALONE_IS_ZERO
test_is_zero: $(LIBRARY)
test_is_zero: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_is_zero: LDFLAGS += $(LIBRARY)
test_is_zero: clean test_is_zero.o
	$(CC) test_is_zero.o -o test_is_zero $(LDFLAGS)
	./test_is_zero

test_help: CFLAGS += -DSTANDALONE_HELP
test_help: $(LIBRARY)
test_help: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_help: LDFLAGS += $(LIBRARY)
test_help: clean $(TEST_OBJ_HELP)
	$(CC) $(TEST_OBJ_HELP) -o ./test_help $(LDFLAGS)
	./test_help

clean:
	rm -rf *.o
	rm -rf *.gcno *.gcda
	rm -rf test_is_zero
	rm -rf test_help
	rm -rf test_help.a

rebuild: clean all

.PHONY: clean all rebuild gcov_report
