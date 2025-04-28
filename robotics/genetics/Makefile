
CC = g++

LIBS = -lm -lpthread

PRG_OBJS= genetics_general.cpp
OBJS= genetics_general.o
PRG_ASM= genetics_asm.cpp
OBJS_ASM= genetics_asm.o
PRG_VSC= genetics_vasconcelos.cpp
OBJS_VSC= genetics_vasconcelos.o
PRG_TRANSFORM= transform_gen.cpp
OBJS_TRANSFORM= transform_gen.o
PRG_COMPARE= compare_raw_files.cpp
OBJS_COMPARE= compare_raw_files.o

genetics_asm: $(OBJS_ASM)
	  $(CC)  -o $@ $(OBJS_ASM) $(LIBS)
 
genetics_vasconcelos: $(OBJS_VSC)
	$(CC)  -o $@ $(OBJS_VSC) $(LIBS)

genetics_general: $(OBJS)
	  $(CC)  -o $@ $(OBJS) $(LIBS)
 
transform_gen: $(OBJS_TRANSFORM)
	  $(CC)  -o $@ $(OBJS_TRANSFORM) $(LIBS)
 
compare_raw_files: $(OBJS_COMPARE)
	  $(CC)  -o $@ $(OBJS_COMPARE) $(LIBS)
 
 
$(OBJS_ASM): $(PRG_ASM)
	  $(CC) -c $*.cpp

$(OBJS_VSC): $(PRG_VSC)
	  $(CC) -c $*.cpp

$(OBJS): $(PRG_OBJS)
	  $(CC) -c $*.cpp

$(OBJS_TRANSFORM): $(PRG_TRANSFORM)
	  $(CC) -c $*.cpp

$(OBJS_COMPARE): $(PRG_COMPARE)
	  $(CC) -c $*.cpp

