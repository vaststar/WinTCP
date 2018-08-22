#ifndef MyObserver_h__
#define MyObserver_h__

#include <WinBaseServer/WinBaseObserver.h>
///////////////////////////////////////////////////////////////////////////
///<summary> 实际处理消息类 .</summary>//////////////////////////////////////////////////
///
///<remarks>  朱正天，2017/7/8.</remarks>/////////////////////////////////
///////////////////////////////////////////////////////////////////////////
class MyObserver : public WinBaseObserver
{
public:
	MyObserver(const SOCKET &sockConnect,const std::string &clientAddr);
	~MyObserver(void);
public:
	void OnCommingMessage(const std::string &message);
private:
	void SendHolePack();//整个一次性发送
	void SendSplitPack();//切割发送
	void SendPointPack();//断点续传
private:
	class ServerObserverPrivate;
	ServerObserverPrivate *_p;
};
#endif // MyObserver_h__

