CC = g++ 

LIBS = -lm -lpthread

OBJS= GoTo_State_Cells.o 
PRG_OBJS= GoTo_State_Cells.cpp

GoTo_State_Cells: $(OBJS)
	  $(CC)  -o $@ $(OBJS) $(LIBS) $(SOCKET_LIBS) $(OBJS_LASER)

$(OBJS): $(PRG_OBJS)
	$(CC) $(CFLAGS) -c $*.cpp 

	
	
