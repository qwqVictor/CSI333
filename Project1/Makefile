CC := gcc
CFLAGS := -I.
DEPS = expr.h
OBJECTS = expr.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean: 
	rm -f $(OBJECTS) main