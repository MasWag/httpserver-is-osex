PRODUCT = httpserver
CFLAGS += -g -O0 -I. -Ilibrary -Itest -pthread
MAIN_OBJS = main.o
OBJS = library/request_parser.o library/whole_conf.o library/header_gen.o library/socket.o library/node.o  library/file.o
TEST_OBJS = test/minunit.o

all:$(PRODUCT)

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(PRODUCT): $(OBJS) $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -f *.o $(PRODUCT)

indent:
	indent *.[ch] library/*.[ch] test/*.[ch] 

test: $(OBJS) $(TEST_OBJS)
	$(CC) -o testfile $^
	./testfile

.PHONY: all clean indent test
