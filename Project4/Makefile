CC := gcc
CFLAGS := -I. -lm -lpthread
DEPS = 
OBJECTS = main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean: 
	rm -rf $(OBJECTS) main