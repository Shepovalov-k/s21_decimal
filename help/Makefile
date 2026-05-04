CC := gcc
CFLAGS = -Wall -Wextra -Werror -I. -I.. $(CFLAGS_EXTERNAL)

OS = $(shell uname -s)


OBJ      := help.o
HELP_LIB := help.a 

SRC     := $(wildcard *.c)
OBJ_SRC := $(SRC:.c=.o)

ifeq ($(OS), Darwin)
	CHECK_PATH = /opt/homebrew/opt/check
	CHECK_CFLAGS = -I$(CHECK_PATH)/include
	CHECK_LDFLAGS = -L$(CHECK_PATH)/lib -lcheck -lm -lpthread
else
	CHECK_LDFLAGS = -L$(CHECK_PATH)/lib -lcheck -lm -lpthread -lsubunit
endif

.PHONY: all clean rebuild

all: $(OBJ)

$(HELP_LIB): $(OBJ)
	ar rcs $(HELP_LIB) $(OBJ)
	rm -rf *.o

$(OBJ): help.h $(OBJ_SRC)
	ld -r $(OBJ_SRC) -o $(OBJ)

gcov_report: CFLAGS += --coverage
gcov_report: $(OBJ_SRC)

%.o: %.c
	$(CC) $(CFLAGS) $(CFLAGS_EXTERNAL) -c $^ -o $@


clean:
	rm -rf *.o
	rm -rf *.gcno *.gcda
	rm -rf *.a

rebuild: clean all

.PHONY: clean all rebuild
