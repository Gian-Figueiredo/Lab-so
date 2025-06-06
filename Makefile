CC = gcc
CFLAGS = -Wall -g

all: helloworld

helloworld: helloworld.o
	$(CC) helloworld.o -o helloworld

helloworld.o: helloworld.c
	$(CC) $(CFLAGS) -c helloworld.c -o helloworld.o

clean:
	rm -f *.o helloworld

.PHONY: all clean