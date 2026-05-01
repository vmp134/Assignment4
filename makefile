CC     = gcc
CFLAGS = -Wall -Wextra -g

SRCS = clientList.c 
OBJS = $(SRCS:.c=.o)

MAIN_SRC = chatd.c 
TEST_SRC = testing.c

.PHONY: all clean test

all: chatd

chatd: $(MAIN_SRC:.c=.o) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TEST_SRC:.c=.o) $(OBJS)
	$(CC) $(CFLAGS) -o testing $^
	./testing

%.o: %.c chatd.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o chatd testing