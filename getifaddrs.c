#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

// argv (const char **) != *const* (or something like that)
#pragma clang diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"

int main(int argc, const char *argv[]) {
	const char *interface = "";
	int quiet = false;

	int opt;
	while ((opt = getopt(argc, argv, "q")) != -1) {
		switch (opt) {
			case 'q': quiet = true; break;
			default:
			  if (!quiet) fprintf(stderr, "Usage: %s [-i] [interface]\n", argv[0]);
			  exit(EXIT_FAILURE);
		}
	}
	if (optind < argc) interface = argv[optind];

	struct ifaddrs *ifaddr;

	if (getifaddrs(&ifaddr) == -1) {
		if (!quiet) perror("getifaddrs");
		freeifaddrs(ifaddr);
		return EXIT_FAILURE;
	}


	for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (!ifa->ifa_addr) continue;

		if (strncmp(ifa->ifa_name, interface, strlen(interface)) != 0 || ifa->ifa_addr->sa_family != AF_INET) continue;

		char host[NI_MAXHOST];
		int s = 0;
		if ((s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST)) != 0) {
			if (!quiet) printf("getnameinfo() failed: %s\n", gai_strerror(s));
			freeifaddrs(ifaddr);
			return EXIT_FAILURE;
		}

		if (quiet) printf("%s\n", host);
		else printf("%s:%s\n", ifa->ifa_name, host);
	}

	freeifaddrs(ifaddr);
	return EXIT_SUCCESS;
}
