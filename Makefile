CC=gcc

BINARY_DIR = bin
INCLUDE_DIR = include

CFLAGS = -O1 -ggdb -Wall -Werror -Wno-missing-field-initializers -pedantic -Wextra -Wconversion -std=gnu11 -I$(INCLUDE_DIR)/
SRCS_INC = $(patsubst %.c,%.o,$(wildcard $(INCLUDE_DIR)/*.c))
_DEPS = strcutures.h
DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

all: main

# Regla para el cliente
main: $(SRCS_INC)
	$(CC) -o $(BINARY_DIR)/$@ $^ $(CFLAGS)

.PHONY: all clean

clean :
	rm -Rf $(BINARY_DIR)/*.o
