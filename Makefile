CC = cc
CFLAGS = -Wall -g

all: principal helloworld

principal: principal.o
	$(CC) principal.o -o principal

helloworld: helloworld.o
	$(CC) helloworld.o -o helloworld

principal.o: principal.c
	$(CC) $(CFLAGS) -c principal.c -o principal.o

helloworld.o: helloworld.c
	$(CC) $(CFLAGS) -c helloworld.c -o helloworld.o

clean:
	rm -f *.o principal helloworld

.PHONY: all clean