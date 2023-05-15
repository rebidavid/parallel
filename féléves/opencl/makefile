CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
LDFLAGS = -lOpenCL

EXECUTABLE = opencl

all: $(EXECUTABLE)

$(EXECUTABLE): opencl.o
	$(CC) -o $@ $^ $(LDFLAGS)

opencl.o: opencl.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECUTABLE) *.o
