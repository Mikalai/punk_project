#include <windows.h>
#include <gl\gl.h>
#include <gl\glext.h>
#include <gl\glu.h>
#include "Driver.h"


#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "Glu32.lib")
#pragma comment(lib, "libjpeg.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Util.lib")
#pragma comment(lib, "System.lib")

Driver* g_driver = 0;

extern "C" __declspec(dllexport) IDriver* GetDriver(DriverInputData* data)
{
	return g_driver;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
	switch(reason)
	{
	case DLL_PROCESS_ATTACH:
		g_driver = new Driver;
		break;
	case DLL_PROCESS_DETACH:
		DELETE_POINTER(g_driver);
		break;
	default:
		break;
	}
	return TRUE;
}#include <windows.h>
#include <gl\gl.h>
#include <gl\glext.h>
#include <gl\glu.h>
#include "Driver.h"


#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "Glu32.lib")
#pragma comment(lib, "libjpeg.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Util.lib")
#pragma comment(lib, "System.lib")

TDriver* g_driver = 0;

extern "C" __declspec(dllexport) IDriver* GetDriver(TDriverInputData* data)
{
	return g_driver;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
	switch(reason)
	{
	case DLL_PROCESS_ATTACH:
		g_driver = new TDriver;
		break;
	case DLL_PROCESS_DETACH:
		DELETE_POINTER(g_driver);
		break;
	default:
		break;
	}
	return TRUE;
}