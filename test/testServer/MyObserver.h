#ifndef MyObserver_h__
#define MyObserver_h__

#include <WinBaseServer/WinBaseObserver.h>
///////////////////////////////////////////////////////////////////////////
///<summary> ʵ�ʴ�����Ϣ�� .</summary>//////////////////////////////////////////////////
///
///<remarks>  �����죬2017/7/8.</remarks>/////////////////////////////////
///////////////////////////////////////////////////////////////////////////
class MyObserver : public WinBaseObserver
{
public:
	MyObserver(const SOCKET &sockConnect,const std::string &clientAddr);
	~MyObserver(void);
public:
	void OnCommingMessage(const std::string &message);
private:
	void SendHolePack();//����һ���Է���
	void SendSplitPack();//�и��
	void SendPointPack();//�ϵ�����
private:
	class ServerObserverPrivate;
	ServerObserverPrivate *_p;
};
#endif // MyObserver_h__

