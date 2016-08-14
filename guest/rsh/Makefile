CFLAGS = -ansi -pedantic -Wall -Wno-unused-result
LIBS = -lm

DEPS = utils.o prompt.o utils.o args.o

rsh: main.o $(DEPS)
	gcc $^ -o $@ $(LIBS)

main.o: main.c
	gcc -c $(CFLAGS) $^

utils.o: utils.c utils.h
	gcc -c $(CFLAGS) $^

args.o: args.c args.h
	gcc -c $(CFLAGS) $^

prompt.o: prompt.c prompt.h utils.h args.h
	gcc -c $(CFLAGS) $^

.PHONY: clean
clean:
	rm *.out *.gch *.o rsh
