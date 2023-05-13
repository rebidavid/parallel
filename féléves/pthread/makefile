CC = gcc
CFLAGS = -Wall -O2 -pthread
TARGET = pthread

all: $(TARGET)

$(TARGET): pthread.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
