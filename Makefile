PRODUCT = httpserver
CFLAGS += -g -O0 -I. -Ilibrary -Itest
MAIN_OBJS = main.o
OBJS = library/request_parser.o
TEST_OBJS = test/minunit.o

all:$(PRODUCT)

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(PRODUCT): $(OBJS) $(MAIN_OBJS)
	$(CC) -o $@ $^

clean: 
	rm -f *.o $(PRODUCT)

indent:
	indent *.[ch] library/*.[ch] test/*.[ch] 

test: $(OBJS) $(TEST_OBJS)
	$(CC) -o testfile $^
	./testfile

.PHONY: all clean indent test
