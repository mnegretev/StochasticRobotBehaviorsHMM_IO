CC = g++ 

LIBS = -lm -lpthread

OBJS= test_python_c.o 
PRG_OBJS= test_python_c.cpp

GoTo_State_Machine: $(OBJS)
	  $(CC)  -o $@ $(OBJS) $(LIBS)

$(OBJS): $(PRG_OBJS)
	$(CC) $(CFLAGS) -c $*.cpp 
	
	
