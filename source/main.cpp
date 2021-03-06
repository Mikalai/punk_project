#ifdef _WIN32

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif	//	_DEBUG

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

#include "system/logger.h"

#ifdef _WIN32

#include <Windows.h>
#include <dshow.h>
#include "system\win32\camera_capture_win32.h"
#pragma comment(lib, "strmiids")

void Init()
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (SUCCEEDED(hr))
    {
        IEnumMoniker *pEnum;

        hr = System::EnumerateDevices(CLSID_VideoInputDeviceCategory, &pEnum);
        if (SUCCEEDED(hr))
        {
            System::DisplayDeviceInformation(pEnum);
            pEnum->Release();
        }
        hr = System::EnumerateDevices(CLSID_AudioInputDeviceCategory, &pEnum);
        if (SUCCEEDED(hr))
        {
            System::DisplayDeviceInformation(pEnum);
            pEnum->Release();
        }
	}
}

void Release()
{
	CoUninitialize();
}

#endif	//	_WIN32

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(160);
	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		out_message() << "punk_engine.dll (" __DATE__" at "__TIME__") attached..." << std::endl;
		Init();
		break;
	case DLL_PROCESS_DETACH:
		out_message() << "punk_engine.dll (" __DATE__" at "__TIME__") detached..." << std::endl;
	//	Release();
		break;
	}
	return TRUE;
}

#endif	//	_WIN32