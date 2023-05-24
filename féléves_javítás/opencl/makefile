<<<<<<< HEAD
CC = gcc
CFLAGS = -std=c99 -Wall
LDFLAGS = -lOpenCL

TARGET = matrix_addition

all: $(TARGET)

$(TARGET): matrix_addition.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

matrix_addition.o: matrix_addition.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)
=======
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
>>>>>>> 83bdacbb457aa0c7f42d6d96a65a597821a58f9a
