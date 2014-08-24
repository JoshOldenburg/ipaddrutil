CC=gcc # I'd use clang, but gcc links to clang on OS X anyways
CFLAGS=-Wall # -Weverything is clang-specific

all: getifaddrs getipfortmux

getifaddrs:
	$(CC) $(CFLAGS) getifaddrs.c -o getifaddrs

getipfortmux:
	$(CC) $(CFLAGS) getipfortmux.c -o getipfortmux

clean:
	rm -rf getifaddrs a.out getipfortmux ./*.dSYM
