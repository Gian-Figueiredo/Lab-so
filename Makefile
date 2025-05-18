CC = cc
CFLAGS = -Wall -g

all: main helloworld

main: main.o
	$(CC) main.o -o main

helloworld: helloworld.o
	$(CC) helloworld.o -o helloworld

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

helloworld.o: helloworld.c
	$(CC) $(CFLAGS) -c helloworld.c -o helloworld.o

clean:
	rm -f *.o main helloworld

.PHONY: all clean