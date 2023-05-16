CC = gcc
CFLAGS = -Wall -Wextra -fopenmp

TARGET = openmp

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm -f $(TARGET)
