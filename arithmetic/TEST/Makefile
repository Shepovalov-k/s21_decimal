CC := gcc
CFLAGS = -Wall -Wextra -Werror -I./include -I../../
LDFLAGS += -fsanitize=address

LIBRARY := ../../s21_decimal.a

OS = $(shell uname -s)

TEST_SRC_ARITHMETIC := $(wildcard *.c)
TEST_OBJ_ARITHMETIC := $(TEST_SRC_ARITHMETIC:.c=.o)

TEST_ARITHMETIC_LIB := test_arithmetic.a

$(TEST_ARITHMETIC_LIB): $(TEST_OBJ_ARITHMETIC)
	ar rcs $(TEST_ARITHMETIC_LIB) $(TEST_OBJ_ARITHMETIC)

ifeq ($(OS), Darwin)
    CHECK_PATH = /opt/homebrew/opt/check
    CHECK_CFLAGS = -I$(CHECK_PATH)/include
    CHECK_LDFLAGS = -L$(CHECK_PATH)/lib -lcheck -lm -lpthread
else
    CHECK_PATH = /usr
    CHECK_CFLAGS = -I$(CHECK_PATH)/include
    CHECK_LDFLAGS = -L$(CHECK_PATH)/lib -lcheck -lm -lpthread -lsubunit
endif

$(LIBRARY):
	$(MAKE) -C ../.. $(notdir $(LIBRARY))

all: test_arithmetic

%.o: %.h
%.o: %.c
	$(CC) $(CFLAGS) $(CFLAGS_EXTERNAL) -c $^ -o $@

test_add: CFLAGS += -DSTANDALONE_ADD
test_add: $(LIBRARY)
test_add: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_add: LDFLAGS += $(LIBRARY)
test_add: clean test_add.o
	$(CC) test_add.o -o test_add $(LDFLAGS)
	./test_add

test_sub: CFLAGS += -DSTANDALONE_SUB
test_sub: $(LIBRARY)
test_sub: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_sub: LDFLAGS += $(LIBRARY)
test_sub: clean test_sub.o
	$(CC) test_sub.o -o test_sub $(LDFLAGS)
	./test_sub

test_mul: CFLAGS += -DSTANDALONE_MUL
test_mul: $(LIBRARY)
test_mul: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_mul: LDFLAGS += $(LIBRARY)
test_mul: clean test_mul.o
	$(CC) test_mul.o -o test_mul $(LDFLAGS)
	./test_mul

test_div: CFLAGS += -DSTANDALONE_DIV
test_div: $(LIBRARY)
test_div: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_div: LDFLAGS += $(LIBRARY)
test_div: clean test_div.o
	$(CC) test_div.o -o test_div $(LDFLAGS)
	./test_div

test_arithmetic: CFLAGS += -DSTANDALONE_ARITHMETIC
test_arithmetic: $(LIBRARY)
test_arithmetic: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_arithmetic: LDFLAGS += $(LIBRARY)
test_arithmetic: clean test_arithmetic.o test_add.o test_sub.o test_mul.o test_div.o
	$(CC) test_arithmetic.o test_add.o test_sub.o test_mul.o test_div.o -o ./test_arithmetic $(LDFLAGS)
	./test_arithmetic


clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.gcno *.gcda
	rm -rf test_add
	rm -rf test_sub
	rm -rf test_mul
	rm -rf test_div
	rm -rf test_arithmetic
	rm -rf test_arithmetic.a

rebuild: clean all

.PHONY: clean all rebuild gcov_report
