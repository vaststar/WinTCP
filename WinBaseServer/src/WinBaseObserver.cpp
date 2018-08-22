#include "WinBaseObserver.h"

#include <thread>
#include <iostream>
#include <mutex>

class WinBaseObserver::ServerObserverPrivate {
public:
	ServerObserverPrivate()
		:isConnected(true)
		, clientAddr("")
		, heartBuff("heart") {
	}
public:
	SOCKET sockConnect;
	bool isConnected;//�Ƿ񱣳�����
	std::string clientAddr;//�ͻ��˵�ַ
	std::string heartBuff;//������Ϣ
	std::mutex dataMutex;
};

WinBaseObserver::WinBaseObserver(const SOCKET &sockConnect, const std::string &clientAddr)
	:_p(new ServerObserverPrivate())
{
	_p->sockConnect = sockConnect;
	_p->clientAddr = clientAddr;
}

WinBaseObserver::~WinBaseObserver()
{
	delete _p;
	_p = nullptr;
}

void WinBaseObserver::HeartBeat() {
	while (_p->isConnected) {
		std::this_thread::sleep_for(std::chrono::seconds(3));
		if (SOCKET_ERROR == _p->sockConnect || SOCKET_ERROR == send(_p->sockConnect, _p->heartBuff.c_str(), sizeof(_p->heartBuff), 0)) {
			std::lock_guard<std::mutex> loc(_p->dataMutex);
			_p->isConnected = false;
			break;
		}
	}
}

void WinBaseObserver::Run() {
	std::cout << "������" << _p->clientAddr << "������!" << std::endl;

	std::shared_ptr<std::thread> heartthread = std::make_shared<std::thread>(&WinBaseObserver::HeartBeat, this);
	std::shared_ptr<std::thread> receiveThread = std::make_shared<std::thread>(&WinBaseObserver::ReceiveMessage, this);

	heartthread->join();
	receiveThread->join();

	std::cout << "�Ͽ���" << _p->clientAddr << "������!" << std::endl;
	closesocket(_p->sockConnect);
}

void WinBaseObserver::ReceiveMessage() {
	while (_p->isConnected) {
		char recvBuf[1024];
		memset(recvBuf, 0, sizeof(recvBuf));
		int rec = recv(_p->sockConnect, recvBuf, sizeof(recvBuf), 0);
		if (rec == 0 || rec == -1) {
			std::lock_guard<std::mutex> loc(_p->dataMutex);
			_p->isConnected = false;
			break;
		}
		if (recvBuf == _p->heartBuff) continue;
		std::cout << "�յ�����" << _p->clientAddr << "����Ϣ��" << std::endl;
		std::cout << recvBuf << std::endl;
		std::cout << "��ʼ�������Ϣ..." << std::endl;

		OnCommingMessage(recvBuf);

		std::cout << "�������!" << std::endl;
	}
}

void WinBaseObserver::OnCommingMessage(const std::string &message) {
}

void WinBaseObserver::startObserver() {
	Run();
}

void WinBaseObserver::SendMessageToClient(const std::string &message) {
	send(_p->sockConnect, message.c_str(), message.length(), 0);
}
