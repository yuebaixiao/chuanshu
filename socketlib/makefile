src = $(wildcard ./src/*.c)
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))

.PHONY:clean

WORKDIR=.

LIB1 = libitcastsocket.so

CC = gcc
CFLGS= -Wall -g -I$(WORKDIR)/inc/

all: $(LIB1) 


$(LIB1):$(obj)
	$(CC) -shared -fPIC $^ -o $@
	mv  $(LIB1) ./lib

$(obj): ./obj/%.o : ./src/%.c ./inc/%.h
	gcc -c $< -o $@ $(CFLGS) -shared -fPIC

clean:
	rm -rf $(obj) ./lib/$(LIB1) 




