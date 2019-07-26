src = $(wildcard *.c)
obj = $(patsubst %.c, %, $(src))

ALL:$(obj)

CFLAGS = -Wall -g -lpthread 
LIBNAME = -litcastsocket
LIBFLAGS = -L$(HOME)/lib

$(obj):%:%.c
	gcc $< -o $@ $(CFLAGS) $(LIBNAME) $(LIBFLAGS)
	
clean:
	-rm -rf $(obj)
	
PHONY: ALL clean
	
