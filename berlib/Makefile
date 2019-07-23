
src = $(wildcard ./src/*.c)
test_src = $(wildcard ./test/*.c)
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))
test_obj = $(patsubst ./test/%.c, ./obj/%.o, $(test_src))

target = app
inc_path = ./inc

ALL:$(target)

$(target):$(obj) $(test_obj)
	gcc -o $@ $^

$(obj): ./obj/%.o : ./src/%.c ./inc/%.h
	gcc -c $< -o $@ -I $(inc_path)


$(test_obj): ./obj/%.o : ./test/%.c
	gcc -c $< -o $@ -I $(inc_path)

clean:

	-rm -rf $(obj) $(test_obj) $(target)

.PHONY: clean ALL
