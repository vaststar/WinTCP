#include <WinSock2.h>
#include <iostream>
#include <sstream>

int main()
{
	WSADATA wsaData;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData)) return false;

	SOCKET socketSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8000);
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	connect(socketSrv, (SOCKADDR*)&addrSrv,sizeof(SOCKADDR_IN));
	send(socketSrv, "int", 3, 0);
	while (true)
	{
		char recvBuf[1024];
		memset(recvBuf, '\0', sizeof(recvBuf));
		int rec = recv(socketSrv, recvBuf, sizeof(recvBuf), 0);
		if(std::string(recvBuf) == "heart") continue;
		int *a = reinterpret_cast<int*>(recvBuf);
		
		std::cout << a[0] << a[1] << a[2];
	}
	WSACleanup();
	return 0;
}