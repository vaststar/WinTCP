#ifndef WinBaseObserver_h__
#define WinBaseObserver_h__

#include "WinBaseServer_global.h"

#include <string>
#include <WinSock2.h>

//////////////////////////////////////////////////////////////////////////
///<summary>����������� </summary>
///
///
///<remarks> 11/1/2017 --������  </remarks>/////////////////////////////
///////////////////////////////////////////////////////////////////////////*/
class WINBASESERVER_LIB_EXPORT WinBaseObserver
{
public:
	WinBaseObserver(const SOCKET &sockConnect, const std::string &clientAddr);
	virtual ~WinBaseObserver();
public:
	///<summary> (�ⲿ����ʹ��) �����죬2017/7/8.</summary>///
	void startObserver();

	///<summary> (��д����Ϣ����)����������Ϣ �����죬2017/7/8.</summary>///
	virtual void OnCommingMessage(const std::string &message) = 0;
public:
	void SendMessageToClient(const std::string &message);

private:
	///<summary> ��Ϣ������ �����죬2017/7/8.</summary>///
	void ReceiveMessage();
	///<summary> ������ �����죬2017/7/8.</summary>///
	void HeartBeat();
	///<summary> �ڲ����к��� �����죬2017/7/8.</summary>///
	void Run();
private:
	class ServerObserverPrivate;
	ServerObserverPrivate *_p;
};
#endif // WinBaseObserver_h__

