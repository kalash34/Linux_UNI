CC=gcc

all: cwiczenie10

cwiczenie10: cwiczenie10.o
	$(CC) -pthread -o $@ $^

cwiczenie10.o: cwiczenie10.c
	$(CC) -c $<

