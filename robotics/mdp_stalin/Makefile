CC = gcc
CFLAGS = -Wall
DEPS = mdp.h dstruct.h
OBJ = dstruct.o mdp.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
file:
	gcc -o file.out dstruct.o mdp.o file.c
