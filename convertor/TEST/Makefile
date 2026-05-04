CC := gcc
CFLAGS = -Wall -Wextra -Werror -I./include -I../../
LDFLAGS = 

OS = $(shell uname -s)

ifneq ($(OS), Darwin)
	CHECK_LDFLAGS=-lcheck -lm -lpthread -lsubunit
else
	CHECK_LDFLAGS=-lcheck -lm -lpthread
endif


LIBRARY := ../../s21_decimal.a

TEST_SRC_CONVERTOR := $(wildcard *.c)
TEST_OBJ_CONVERTOR := $(TEST_SRC_CONVERTOR:.c=.o)

TEST_CONVERTOR_LIB := test_convertor.a

$(TEST_CONVERTOR_LIB): $(TEST_OBJ_CONVERTOR)
	ar rcs $(TEST_CONVERTOR_LIB) $(TEST_OBJ_CONVERTOR)


$(LIBRARY):
	$(MAKE) -C ../.. $(notdir $(LIBRARY))


SOURCES = test_convertor.c
OBJ_SRC = $(SOURCES:.c=.o)

all: test_convertor

test_from_decimal_to_float: CFLAGS += -DSTANDALONE_FROM_DECIMAL_TO_FLOAT
test_from_decimal_to_float: $(LIBRARY)
test_from_decimal_to_float: LDFLAGS += $(CHECK_LDFLAGS)
test_from_decimal_to_float: LDFLAGS += $(LIBRARY)
test_from_decimal_to_float: clean test_from_decimal_to_float.o
	$(CC) test_from_decimal_to_float.o -o test_from_decimal_to_float $(LDFLAGS)
	./test_from_decimal_to_float

test_from_decimal_to_int: CFLAGS += -DSTANDALONE_FROM_DECIMAL_TO_INT
test_from_decimal_to_int: $(LIBRARY)
test_from_decimal_to_int: LDFLAGS += $(CHECK_LDFLAGS)
test_from_decimal_to_int: LDFLAGS += $(LIBRARY)
test_from_decimal_to_int: clean test_from_decimal_to_int.o
	$(CC) test_from_decimal_to_int.o -o test_from_decimal_to_int $(LDFLAGS)
	./test_from_decimal_to_int

test_convertor: CFLAGS += -DSTANDALONE_CONVERTOR
test_convertor: $(LIBRARY)
test_convertor: LDFLAGS += $(CHECK_LDFLAGS)
test_convertor: LDFLAGS += $(LIBRARY)
test_convertor: clean test_convertor.o test_from_decimal_to_float.o test_from_decimal_to_int.o test_from_int_to_decimal.o test_from_float_to_decimal.o
	$(CC) test_convertor.o test_from_decimal_to_float.o test_from_decimal_to_int.o test_from_int_to_decimal.o test_from_float_to_decimal.o -o ./test_convertor $(LDFLAGS)
	./test_convertor


%.o: %.h
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o
	rm -rf *.gcno *.gcda
	rm -rf test_from_decimal_to_float
	rm -rf test_from_decimal_to_int
	rm -rf test_convertor
	rm -rf test_convertor.a

rebuild: clean all

.PHONY: clean all rebuild gcov_report
