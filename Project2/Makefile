CC := gcc
CFLAGS := -I. -lm
DEPS = linkedlist.h
OBJECTS = linkedlist.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean: 
	rm -f $(OBJECTS) main