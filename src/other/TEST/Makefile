CC := gcc
CFLAGS = -Wall -Wextra -Werror -I./include -I../../
LDFLAGS = 

OS = $(shell uname -s)

LIBRARY := ../../s21_decimal.a

TEST_SRC_ARITHMETIC := $(wildcard *.c)
TEST_OBJ_ARITHMETIC := $(TEST_SRC_ARITHMETIC:.c=.o)

TEST_ARITHMETIC_LIB := test_other.a

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

test_negate: CFLAGS += -DSTANDALONE_NEGATE
test_negate: $(LIBRARY)
test_negate: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_negate: LDFLAGS += $(LIBRARY)
test_negate: clean test_negate.o
	$(CC) test_negate.o -o test_negate $(LDFLAGS)
	./test_negate

test_other: CFLAGS += -DSTANDALONE_OTHER
test_other: $(LIBRARY)
test_other: LDFLAGS += -lcheck -lm -lpthread -lsubunit
test_other: LDFLAGS += $(LIBRARY)
test_other: clean test_other.o test_floor.o test_round.o test_truncate.o test_negate.o
	$(CC) test_other.o test_floor.o test_round.o test_truncate.o test_negate.o -o ./test_other $(LDFLAGS)
	./test_other


clean:
	rm -rf *.o
	rm -rf *.gcno *.gcda
	rm -rf test_other test_negate
	rm -rf test_other.a

rebuild: clean all

.PHONY: clean all rebuild gcov_report
