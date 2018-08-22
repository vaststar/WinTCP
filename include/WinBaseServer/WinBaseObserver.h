#ifndef WinBaseObserver_h__
#define WinBaseObserver_h__

#include "WinBaseServer_global.h"

#include <string>
#include <WinSock2.h>

//////////////////////////////////////////////////////////////////////////
///<summary>服务处理基本类 </summary>
///
///
///<remarks> 11/1/2017 --朱正天  </remarks>/////////////////////////////
///////////////////////////////////////////////////////////////////////////*/
class WINBASESERVER_LIB_EXPORT WinBaseObserver
{
public:
	WinBaseObserver(const SOCKET &sockConnect, const std::string &clientAddr);
	virtual ~WinBaseObserver();
public:
	///<summary> (外部运行使用) 朱正天，2017/7/8.</summary>///
	void startObserver();

	///<summary> (重写该消息处理)处理传来的消息 朱正天，2017/7/8.</summary>///
	virtual void OnCommingMessage(const std::string &message) = 0;
public:
	void SendMessageToClient(const std::string &message);

private:
	///<summary> 消息处理函数 朱正天，2017/7/8.</summary>///
	void ReceiveMessage();
	///<summary> 心跳包 朱正天，2017/7/8.</summary>///
	void HeartBeat();
	///<summary> 内部运行函数 朱正天，2017/7/8.</summary>///
	void Run();
private:
	class ServerObserverPrivate;
	ServerObserverPrivate *_p;
};
#endif // WinBaseObserver_h__

