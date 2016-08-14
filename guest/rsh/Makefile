CFLAGS = -ansi -pedantic -Wall -Wno-unused-result
LIBS = -lm

DEBUG = false
DEPS = args.o prompt.o builtin.o proc.o ustring.o utils.o

ifeq ($(DEBUG), true)
	CFLAGS += -g
endif

rsh: main.o $(DEPS)
	gcc $^ -o $@ $(LIBS)

main.o: main.c
	gcc -c $(CFLAGS) $^

args.o: args.c args.h ustring.h
	gcc -c $(CFLAGS) $^

prompt.o: prompt.c prompt.h utils.h args.h builtin.h proc.h ustring.h
	gcc -c $(CFLAGS) $^

builtin.o: builtin.c builtin.h utils.h args.h ustring.h
	gcc -c $(CFLAGS) $^

proc.o: proc.c proc.h utils.h ustring.h args.h
	gcc -c $(CFLAGS) $^

ustring.o: ustring.c ustring.h
	gcc -c $(CFLAGS) $^

utils.o: utils.c utils.h
	gcc -c $(CFLAGS) $^

.PHONY: clean
clean:
	rm *.out *.gch *.o rsh
