#ifdef _WIN32

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif	//	_DEBUG


#include <Windows.h>

#include "system/logger.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(177);
	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		out_message() << "punk_engine.dll (" __DATE__" at "__TIME__") attached..." << std::endl;
		break;
	case DLL_PROCESS_DETACH:
		out_message() << "punk_engine.dll (" __DATE__" at "__TIME__") detached..." << std::endl;
		break;
	}
	return TRUE;
}

#endif	//	_WIN32