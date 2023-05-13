CC = gcc
CFLAGS = -Wall -O2 -DCL_TARGET_OPENCL_VERSION=220
LDFLAGS = -lOpenCL
TARGET = opencl
SRCS = opencl.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
