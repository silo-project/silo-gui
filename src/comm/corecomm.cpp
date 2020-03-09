#include <iostream>
#include <sys/socket.h>

#include "corecomm.hpp"

using namespace std;

namespace CoreComm {

	int sockfd;

	int connect() {
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0) {
			cout << "ERROR opening socket" << endl;
			return -1;
		}

		struct sockaddr_in serv_addr;
		memset(&serv_addr, 0x00, sizeof(struct sockaddr_in));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = inet_addr(COMM_ADDR);
		serv_addr.sin_port = htons(COMM_PORT);

		int connected = connect(sockfd, *serv_addr, sizeof(struct socketaddr_in));
		if (connected < 0) {
			cout << "ERROR connecting" << endl;
			close(sockfd);
			return -1;
		}

		return 0;
	}

	void disconnect() {
		close(sockfd);
	}
}