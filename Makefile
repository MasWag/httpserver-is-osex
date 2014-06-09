PRODUCT = httpserver
CFLAGS += -g -O3
OBJS = main.o

all:$(PRODUCT)

$(PRODUCT): $(OBJS)
	$(CC) -o $@ $^

clean: 
	rm -f *.o $(PRODUCT)

indent:
	indent *.c

.PHONY: all clean indent
