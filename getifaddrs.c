#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char *argv[]) {
	const char *interface = "";
	if (argc > 1) interface = argv[1];

	struct ifaddrs *ifaddr;

	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs");
		freeifaddrs(ifaddr);
		return EXIT_FAILURE;
	}


	for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (!ifa->ifa_addr) continue;

		if (strncmp(ifa->ifa_name, interface, strlen(interface)) != 0 || ifa->ifa_addr->sa_family != AF_INET) continue;

		char host[NI_MAXHOST];
		int s = 0;
		if ((s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST)) != 0) {
			printf("getnameinfo() failed: %s\n", gai_strerror(s));
			freeifaddrs(ifaddr);
			return EXIT_FAILURE;
		}

		printf("%s:%s\n", ifa->ifa_name, host);
	}

	freeifaddrs(ifaddr);
	return EXIT_SUCCESS;
}
