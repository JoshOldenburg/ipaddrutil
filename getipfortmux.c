#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static const char *homeStatic = "192.168.1.151";
static const char *homePrefix = "192.168.1.";
static const char *homeNetmask = "255.255.255.0";
static const char *defaultInterface = "en1";

int streql(const char *, const char *);

int main(int argc, const char *argv[]) {
	const char *interface = defaultInterface;
	if (argc > 1) interface = argv[1];

	struct ifaddrs *ifaddr;

	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs");
		freeifaddrs(ifaddr);
		return EXIT_FAILURE;
	}

	int hasPrintedAddress = 0;
	int interfaceHasAddress = 0;

	for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (!ifa->ifa_addr) continue; // Filter out things without an address

		if (!streql(ifa->ifa_name, interface)) continue; // Skip if not correct interface
		if (ifa->ifa_addr->sa_family != AF_INET) continue; // Skip if no address

		interfaceHasAddress = 1;

		char host[NI_MAXHOST]; // Will be the IP
		int s = 0;
		if ((s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST)) != 0) {
			printf("getnameinfo() failed: %s\n", gai_strerror(s));
			freeifaddrs(ifaddr);
			return EXIT_FAILURE;
		}

		int isHomeStatic = streql(host, homeStatic);

		if (isHomeStatic) continue; // Filter out the static IP
		else if (streql(host, homePrefix) && !isHomeStatic) { // Starts with the right prefix
			char netmask[NI_MAXHOST];
			if ((s = getnameinfo(ifa->ifa_netmask, sizeof(struct sockaddr_in), netmask, NI_MAXHOST, NULL, 0, NI_NUMERICHOST)) != 0) {
				printf("getnameinfo() (netmask) failed: %s\n", gai_strerror(s));
				freeifaddrs(ifaddr);
				return EXIT_FAILURE;
			}

			if (streql(netmask, homeNetmask)) sprintf(host, "%sH", host); // Same netmask, likely a home network
			else sprintf(host, "%sN", host); // Same prefix as home, different netmask
		}

		printf("%s", host);
		hasPrintedAddress = 1;
	}

	if (!hasPrintedAddress && interfaceHasAddress) printf("%sND", homeStatic);
	else if (!interfaceHasAddress) printf("no network");

	freeifaddrs(ifaddr);
	return EXIT_SUCCESS;
}

// Returns 1 if both are equal, or 0 otherwise
int streql(const char *a, const char *b) {
	return (strncmp(a, b, strlen(b)) == 0);
}
