CC := gcc
CFLAGS = -Wall -Wextra -Werror -I. -I.. -I../help $(CFLAGS_EXTERNAL)

OS = $(shell uname -s)

OBJ := convertor.o

ifeq ($(OS), Darwin)
	CHECK_PATH = /opt/homebrew/opt/check
	CHECK_CFLAGS = -I$(CHECK_PATH)/include
	CHECK_LDFLAGS = -L$(CHECK_PATH)/lib -lcheck -lm -lpthread
else
	CHECK_LDFLAGS = -L$(CHECK_PATH)/lib -lcheck -lm -lpthread -lsubunit
endif

SOURCES = s21_from_int_to_decimal.c  s21_from_float_to_decimal.c \
          s21_from_decimal_to_int.c  s21_from_decimal_to_float.c
OBJ_SRC = $(SOURCES:.c=.o)

all: $(OBJ)

$(OBJ): $(OBJ_SRC)
	ld -r $(OBJ_SRC) -o $@
	rm -rf $(OBJ_SRC)

gcov_report: CFLAGS += --coverage
gcov_report: $(OBJ)

%.o: %.h
%.o: %.c
	$(CC) $(CFLAGS) $(CFLAGS_EXTERNAL) -c $^ -o $@

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.gcno *.gcda

rebuild: clean all

.PHONY: clean all rebuild gcov_report
