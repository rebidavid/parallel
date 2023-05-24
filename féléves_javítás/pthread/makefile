<<<<<<< HEAD
CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = matrix_addition
SRCS = matrix_addition.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
=======
CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = matrix_addition
SRCS = matrix_addition.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
>>>>>>> 83bdacbb457aa0c7f42d6d96a65a597821a58f9a
