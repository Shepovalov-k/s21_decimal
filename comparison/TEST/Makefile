CC := gcc
CFLAGS = -Wall -Wextra -Werror -I./include -I../../
LDFLAGS = 

OS = $(shell uname -s)

LIBRARY             := ../../s21_decimal.a
TEST_COMPARISON_LIB := test_comparison.a

TEST_SRC_COMPARISON := $(wildcard *.c)
TEST_OBJ_COMPARISON := $(TEST_SRC_COMPARISON:.c=.o)

$(TEST_COMPARISON_LIB): $(TEST_OBJ_COMPARISON)
	ar rcs $(TEST_COMPARISON_LIB) $(TEST_OBJ_COMPARISON)

$(LIBRARY):
	$(MAKE) -C ../.. $(notdir $(LIBRARY))

%.c: %.h
%.o: %.c
	$(CC) $(CFLAGS) $(CFLAGS_EXTERNAL) -c $< -o $@

test_is_equal: CFLAGS += -DSTANDALONE_IS_EQUAL
test_is_equal: $(LIBRARY)
test_is_equal: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_is_equal: LDFLAGS += $(LIBRARY)
test_is_equal: clean test_is_equal.o
	$(CC) test_is_equal.o -o test_is_equal $(LDFLAGS)
	./test_is_equal

test_is_not_equal: CFLAGS += -DSTANDALONE_IS_NOT_EQUAL
test_is_not_equal: $(LIBRARY)
test_is_not_equal: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_is_not_equal: LDFLAGS += ../../$(LIBRARY)
test_is_not_equal: clean test_is_not_equal.o
	$(CC) test_is_not_equal.o -o test_is_not_equal $(LDFLAGS)
	./test_is_not_equal

test_is_greater: CFLAGS += -DSTANDALONE_IS_GREATER
test_is_greater: $(LIBRARY)
test_is_greater: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_is_greater: LDFLAGS += ../../$(LIBRARY)
test_is_greater: clean test_is_greater.o
	$(CC) test_is_greater.o -o test_is_greater $(LDFLAGS)
	./test_is_greater

test_is_greater_or_equal: CFLAGS += -DSTANDALONE_IS_GREATER_OR_EQUAL
test_is_greater_or_equal: $(LIBRARY)
test_is_greater_or_equal: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_is_greater_or_equal: LDFLAGS += $(LIBRARY)
test_is_greater_or_equal: clean test_is_greater_or_equal.o
	$(CC) test_is_greater_or_equal.o -o test_is_greater_or_equal $(LDFLAGS)
	./test_is_greater_or_equal

test_is_less: CFLAGS += -DSTANDALONE_IS_LESS
test_is_less: $(LIBRARY)
test_is_less: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_is_less: LDFLAGS += $(LIBRARY)
test_is_less: clean test_is_less.o
	$(CC) test_is_less.o -o test_is_less $(LDFLAGS)
	./test_is_less

test_is_less_or_equal: CFLAGS += -DSTANDALONE_IS_LESS_OR_EQUAL
test_is_less_or_equal: $(LIBRARY)
test_is_less_or_equal: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_is_less_or_equal: LDFLAGS += $(LIBRARY)
test_is_less_or_equal: clean test_is_less_or_equal.o
	$(CC) test_is_less_or_equal.o -o test_is_less_or_equal $(LDFLAGS)
	./test_is_less_or_equal


test_comparison: CFLAGS += -DSTANDALONE_COMPARISON
test_comparison: $(LIBRARY)
test_comparison: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_comparison: LDFLAGS += $(LIBRARY)
test_comparison: clean test_comparison.o test_is_equal.o test_is_not_equal.o test_is_greater.o test_is_greater_or_equal.o test_is_less.o test_is_less_or_equal.o
	$(CC) test_comparison.o test_is_equal.o test_is_not_equal.o test_is_greater.o test_is_greater_or_equal.o test_is_less.o test_is_less_or_equal.o -o test_comparison $(LDFLAGS)
	./test_comparison



OBJ := test_comparison.o





ifeq ($(OS), Darwin)
	CHECK_PATH = /opt/homebrew/opt/check
	CHECK_CFLAGS = -I$(CHECK_PATH)/include
	CHECK_LDFLAGS = -L$(CHECK_PATH)/lib -lcheck -lm -lpthread
else
	CHECK_LDFLAGS = -L$(CHECK_PATH)/lib -lcheck -lm -lpthread -lsubunit
endif

SOURCES = test_comparison.c
OBJ_SRC = $(SOURCES:.c=.o)

all: $(OBJ)

gcov_report: CFLAGS += --coverage
gcov_report: $(OBJ)

clean:
	rm -rf *.o
	rm -rf *.gcno *.gcda
	rm -rf test_comparison test_is_equal test_is_not_equal test_is_greater
	rm -rf test_is_greater_or_equal test_is_less test_is_less_or_equal
	rm -rf *.a

rebuild: clean all

.PHONY: clean all rebuild gcov_report
