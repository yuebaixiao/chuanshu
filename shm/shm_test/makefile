src = $(wildcard *.c)
obj = $(patsubst %.c, %, $(src))

ALL:$(obj)

CFLAGS = -Wall -g 
#LIBNAME = -litcastsocket
#LIBFLAGS = -L$(HOME)/lib     #LD_LIBRARY_PAHT=$(HOME)/lib

$(obj):%:%.c
	gcc $< -o $@ $(CFLAGS)  
	
clean:
	-rm -rf $(obj)
	
PHONY: ALL clean
	
