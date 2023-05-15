CC = gcc
CFLAGS = -Wall -Wextra -pthread

TARGET = pthread

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm -f $(TARGET)
