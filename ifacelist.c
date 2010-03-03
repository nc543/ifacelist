#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <arpa/inet.h>

int main()
{
	struct ifreq ifreqs[10];
	struct ifconf ifc;
	int i, n;
	int s;

	s = socket(AF_INET, SOCK_STREAM, 0);

	memset(&ifc, 0, sizeof(ifc));
	ifc.ifc_buf = (char*)ifreqs;
	ifc.ifc_len = sizeof(ifreqs);
	if (ioctl(s, SIOCGIFCONF, &ifc) < 0) {
		perror("ioctl(SIOGIFCONF)");
		exit(-1);
	}

	close(s);

	n = ifc.ifc_len/sizeof(struct ifreq);

	printf("%d interfaces:\n", n);
	for(i = 0; i < n; i++) {
		printf("\t%-10s\t%s\n", ifreqs[i].ifr_name, inet_ntoa(((struct sockaddr_in *)&ifreqs[i].ifr_ifru.ifru_addr)->sin_addr));
	}
}

