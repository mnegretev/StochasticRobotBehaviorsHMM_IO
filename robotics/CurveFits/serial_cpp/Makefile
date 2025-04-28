CC = g++


LIBS = -lm -lpthread

PRG_OBJS= serial_cf.cpp lib_house.cpp seriallib.cpp
OBJS= serial_cf.o lib_house.o seriallib.o

serial_cf: $(OBJS)
	  $(CC)  -o $@ $(OBJS)  $(LIBS) 


$(OBJS): $(PRG_OBJS)
	$(CC) $(CFLAGS) -c $*.cpp 

