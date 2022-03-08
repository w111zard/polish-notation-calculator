PROGRAM_NAME = calc

$(PROGRAM_NAME): $(patsubst %.c, %.o, $(wildcard *.c))
	gcc $^ -g -o $@

%.o: %.c
	gcc -g -c -MD $<

include $(wildcard *.d)

.PHONY: clean

clean:
	-rm $(PROGRAM_NAME) $(wildcard *.d *.o)
