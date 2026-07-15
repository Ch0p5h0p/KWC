CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=199309L -DWLR_USE_UNSTABLE

CFLAGS += $(shell pkg-config --cflags wlroots-0.20 wayland-server)
LDLIBS += $(shell pkg-config --libs wlroots-0.20 wayland-server) -lrt

.PHONY: all clean

all: client server

client: src/client.o
	$(CC) $^ $(LDLIBS) -o $@

server: src/server.o src/output.o
	$(CC) $^ $(LDLIBS) -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f client server src/*.o