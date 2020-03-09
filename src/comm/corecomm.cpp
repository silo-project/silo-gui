#include <iostream>

#include "corecomm.hpp"

using namespace std;


#ifdef _WIN32
#include <WinSock2.h>

namespace CoreComm {

	SOCKET sock;
	WSADATA wsaData;

	int connect() {
		if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
			cout << "WSAStartup error " << WSAGetLastError() << endl;
			WSACleanup();
			return -1;
		}

		SOCKADDR_IN serv_addr;
		serv_addr.sin_family = AF_INET; // address family Internet
		serv_addr.sin_port = htons(COMM_PORT); //Port to connect on
		serv_addr.sin_addr.s_addr = inet_addr(COMM_ADDR); //Target IP


		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
		if (sock == INVALID_SOCKET)
		{
			cout << "socket() error : " << WSAGetLastError() << endl;
			WSACleanup();
			return -1;
		}


		if (connect(sock, reinterpret_cast<SOCKADDR *>(&serv_addr), sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
		{
			cout << "connect() error : " << WSAGetLastError() << endl;
			WSACleanup();
			return -1;
		}
		
		return 0;
	}

	void disconnect() {
		closesocket(sock);
		WSACleanup();
	}
}

#else
#include <sys/socket.h>

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
#endif