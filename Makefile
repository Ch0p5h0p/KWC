CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=199309L -DWLR_USE_UNSTABLE

CFLAGS += $(shell pkg-config --cflags wlroots-0.20 wayland-server)
LDLIBS += $(shell pkg-config --libs wlroots-0.20 wayland-server) -lrt

.PHONY: all
.PHONY: clean

all: client server

client:
	$(CC) $(CFLAGS) src/client.c $(LDLIBS) -o client

server:
	$(CC) $(CFLAGS) src/server.c $(LDLIBS) -o server

clean:
	echo "implement me!"