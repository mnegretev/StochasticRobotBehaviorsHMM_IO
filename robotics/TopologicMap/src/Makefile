#CC = g++


#OBJS= wrl_to_map.o
#PRG_OBJS = wrl_to_map.cpp

#generate: $(OBJS)
#          $(CC) -o wrl_to_map $(OBJS) $(LIBS)

#$(OBJS):  $(PRG_OBJS)
#          $(CC) -c $*.cpp 

CC = g++
CFLAGS = -g -Wall -O2
SRC = polygon_expansion.cpp definition.h parserFileWRL.h utilMap.h intersectionTest.h  triangulateVertex.h  utilSimulator.h
OBJ = polygon_expansion.o
#LIBS = -lm

all: $(OBJ)
		$(CC) $(CFLAGS) -o polygon_expansion $(OBJ) #-l $(LIBS) 

clean:
		$(RM) $(OBJ) polygon_expansion

