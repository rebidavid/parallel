CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -fopenmp

.PHONY: all clean

all: matrix_addition

matrix_addition: matrix_addition.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f matrix_addition
