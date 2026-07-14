CC = gcc
CFLAGS = -Wall -Wextra -std=c11

CFLAGS += $(shell pkg-config --cflags wlroots-0.20)
LDLIBS += $(shell pkg-config --libs wlroots-0.20)

.PHONY: all
.PHONY: clean

all: client server

client: src/client.c
	$(CC) $(CFLAGS) src/client.c $(LDLIBS) -o client

server: src/server.c
	$(CC) $(CFLAGS) src/server.c $(LDLIBS) -o server

clean:
	echo "implement me!"