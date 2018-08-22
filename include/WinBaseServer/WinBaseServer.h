#ifndef WinBaseServer_h__
#define WinBaseServer_h__

#include "WinBaseServer_global.h"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <memory>
#include <thread>
//////////////////////////////////////////////////////////////////////////
///<summary>服务器类（重写observer即可使用） </summary>
///
///
///<remarks> 11/1/2018 --朱正天  </remarks>/////////////////////////////
///////////////////////////////////////////////////////////////////////////*/
class WINBASESERVER_LIB_EXPORT WinBaseServer
{
public:
	WinBaseServer( int port = 8000, int maxConnect = 100000);
	virtual ~WinBaseServer();
public:
	template<typename T>
	void startServer();
private:
	///<summary> 初始化socket 朱正天，2017/7/8.</summary>///
	bool InitServer();
private:
	SOCKET AcceptConnect(SOCKADDR_IN &addrClient, int &len);
private:
	class ServerBasePrivate;
	ServerBasePrivate *_p;
};

template<typename T>
void WinBaseServer::startServer()
{
	if (!InitServer()) return;

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR_IN);
	SOCKET sockConnect;

	while (true)
	{
		sockConnect = AcceptConnect(addrClient, len);
		if (SOCKET_ERROR == sockConnect) break;

		//建立连接后，放入线程处理，自身继续等待连接
		std::shared_ptr<std::thread> mythread = std::make_shared<std::thread>([=]() {
			char str[INET_ADDRSTRLEN];
			std::shared_ptr<T> obs = std::make_shared<T>(sockConnect, inet_ntop(AF_INET,(PVOID)&addrClient.sin_addr,str,sizeof(str)));
			obs->startObserver();
		});
		mythread->detach();
	}
}

#endif // WinBaseServer_h__
