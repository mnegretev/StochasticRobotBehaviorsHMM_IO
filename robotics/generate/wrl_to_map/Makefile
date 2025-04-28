#CC = g++

#LIBS = -lm

#OBJS= wrl_to_map.o
#PRG_OBJS = wrl_to_map.cpp

#generate: $(OBJS)
#          $(CC) -o wrl_to_map $(OBJS) $(LIBS)

#$(OBJS):  $(PRG_OBJS)
#          $(CC) -c $*.cpp 

CC = g++
CFLAGS = -g -Wall -O2
SRC = wrl_to_map.cpp definition.h parserFileWRL.h BresenhamAlgorithm.h
OBJ = wrl_to_map.o

all: $(OBJ)
		$(CC) $(CFLAGS) -o wrl_to_map $(OBJ)

clean:
		$(RM) $(OBJ) wrl_to_map

