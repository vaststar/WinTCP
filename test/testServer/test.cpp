#include "MyObserver.h"
#include <WinBaseServer/WinBaseServer.h>
int main()
{
	WinBaseServer a(8000, 10);
	a.startServer<MyObserver>();
	return 0;
}