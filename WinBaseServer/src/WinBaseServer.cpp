#include "WinBaseServer.h"

class WinBaseServer::ServerBasePrivate {
public:
	ServerBasePrivate()
		:port(8000), maxConnect(100000) {
	}
public:
	SOCKET       socketSrv;//服务器socket
	SOCKADDR_IN  addrSrv;//监听地址和端口
	int			 port;//监听端口
	int			 maxConnect;
};

WinBaseServer::WinBaseServer( int port /*= 8000*/,  int maxConnect /*= 1000*/)
	:_p(new ServerBasePrivate())
{
	_p->port = port;
	_p->maxConnect = maxConnect;
}

WinBaseServer::~WinBaseServer()
{
	closesocket(_p->socketSrv);
	WSACleanup();
	delete _p;
}

bool WinBaseServer::InitServer()
{
	WSADATA wsaData;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData)) return false;

	_p->socketSrv = socket(AF_INET, SOCK_STREAM, 0);

	_p->addrSrv.sin_family = AF_INET;
	_p->addrSrv.sin_port = htons(_p->port);
	_p->addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (SOCKET_ERROR == bind(_p->socketSrv, (LPSOCKADDR)&_p->addrSrv, sizeof(SOCKADDR_IN))) return false;

	if (SOCKET_ERROR == listen(_p->socketSrv, _p->maxConnect)) return false;

	return true;
}

SOCKET WinBaseServer::AcceptConnect(SOCKADDR_IN &addrClient, int &len)
{
	return accept(_p->socketSrv, (SOCKADDR*)&addrClient, &len);
}
