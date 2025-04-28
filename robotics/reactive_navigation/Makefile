CC = g++ 

LIBS = -lm -lpthread

OBJS= GoTo_Reactive_Navigation.o 
PRG_OBJS= GoTo_Reactive_Navigation.cpp

GoTo_Reactive_Navigation: $(OBJS)
	  $(CC)  -o $@ $(OBJS) $(LIBS) $(SOCKET_LIBS) $(OBJS_LASER)

$(OBJS): $(PRG_OBJS)
	$(CC) $(CFLAGS) -c $*.cpp 
	
	
