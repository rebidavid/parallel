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
	rm -f $(TARGET) *.o
