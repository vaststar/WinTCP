#ifndef WinBaseServer_global_h__
#define WinBaseServer_global_h__

#ifdef WINBASESERVER_LIB
#define WINBASESERVER_LIB_EXPORT _declspec(dllexport)
#else
#define WINBASESERVER_LIB_EXPORT _declspec(dllimport)
#endif

#endif // WinBaseServer_global_h__
