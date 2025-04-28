CC = gcc
CFLAGS = -Wall
DEPS = mdp.h
OBJ = ryn_chapter_17.o mdp.o 

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

ryn_chapter_17: $(OBJ)
	gcc $(CFLAGS) -o $@ $^
