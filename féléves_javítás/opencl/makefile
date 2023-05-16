CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lOpenCL
TARGET = matrix_addition

all: $(TARGET)

$(TARGET): matrix_addition.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

matrix_addition.o: matrix_addition.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) matrix_addition.o
