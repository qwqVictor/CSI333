CC := gcc
CFLAGS := -I. -lm
DEPS = expr.h radix.h
OBJECTS = expr.o radix.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean: 
	rm -f $(OBJECTS) main