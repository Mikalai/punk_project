#include <windows.h>
#include "Manager.h"

#pragma comment(lib, "Util.lib")

GUIManager* g_manager = NULL;

extern "C" __declspec(dllexport) GUIManager* GetGUIManager()
{
	return g_manager;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
	switch(reason)
	{
	case DLL_PROCESS_ATTACH:
		g_manager = new GUIManager;
		break;
	case DLL_PROCESS_DETACH:
		delete g_manager;
		break;
	default:
		break;
	}
	return TRUE;
}