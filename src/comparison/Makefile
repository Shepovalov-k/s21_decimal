CC := gcc
CFLAGS = -Wall -Wextra -Werror -I. -I.. $(CFLAGS_EXTERNAL)

OS = $(shell uname -s)

OBJ            := comparison.o
COMPARISON_LIB := comparison.a

ifeq ($(OS), Darwin)
	CHECK_PATH = /opt/homebrew/opt/check
	CHECK_CFLAGS = -I$(CHECK_PATH)/include
	CHECK_LDFLAGS = -L$(CHECK_PATH)/lib -lcheck -lm -lpthread
else
	CHECK_LDFLAGS = -L$(CHECK_PATH)/lib -lcheck -lm -lpthread -lsubunit
endif

SOURCES = s21_is_less.c    s21_is_less_or_equal.c \
          s21_is_greater.c s21_is_greater_or_equal.c \
		  s21_is_equal.c   s21_is_not_equal.c
OBJ_SRC = $(SOURCES:.c=.o)

all: $(COMPARISON_LIB)

$(COMPARISON_LIB): $(OBJ)
	ar rcs $(COMPARISON_LIB) $(OBJ)

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
