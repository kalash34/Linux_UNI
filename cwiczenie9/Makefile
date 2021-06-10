CC=gcc

all: cw9

cw9: cw9.o
	$(CC) -lpthread -o $@ $^

cw9.o: cw9.c
	$(CC) -c $<
