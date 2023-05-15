CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -fopenmp
LDFLAGS = -fopenmp

TARGET = openmp

all: $(TARGET)

$(TARGET): openmp.o
	$(CC) $(LDFLAGS) -o $(TARGET) openmp.o

openmp.o: openmp.c
	$(CC) $(CFLAGS) -c openmp.c

clean:
	rm -f $(TARGET) *.o
