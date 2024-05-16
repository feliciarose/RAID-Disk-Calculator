CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2
LDFLAGS =

SRC = raid.c
EXECUTABLE = raid

all: $(EXECUTABLE)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean

