CC=gcc # I'd use clang, but gcc links to clang on OS X anyways
CFLAGS=-Wall # -Weverything is clang-specific

all: getifaddrs

getifaddrs:
	$(CC) $(CFLAGS) getifaddrs.c -o getifaddrs

clean:
	rm getifaddrs a.out
