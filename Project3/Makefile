CC := gcc
CFLAGS := -I. -lm
DEPS = main.h util.h copy.h move.h
OBJECTS = main.o util.o copy.o move.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)
	mkdir -p bin
	ln main bin/copy bin/move

.PHONY: clean
clean: 
	rm -f $(OBJECTS) main bin