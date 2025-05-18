CC = cc
CFLAGS = -Wall

all: programa

programa: principal.o helloworld.o
	$(CC) $(CFLAGS) -o principal.o helloworld.o

principal.o: principal.c
	$(CC) $(CFLAGS) -c principal.c

helloworld.o: helloworld.c
	$(CC) $(CFLAGS) -c helloworld.c

clean:
	rm -f *.o programa

.PHONY: all clean