#ifdef _WIN32

// ATTENTION: under construction

#ifndef _H_PUNK_SYSTEM_CAMERA_CAPTURE
#define _H_PUNK_SYSTEM_CAMERA_CAPTURE

#include "../../config.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <dshow.h>

namespace Gpu
{
		class Texture2D;
}

namespace System
{
	void PUNK_ENGINE_API SetCriticalSection(CRITICAL_SECTION* cs);
	void PUNK_ENGINE_API SetTexture(void* buffer, int* len);

	void PUNK_ENGINE_API TestCamera();

	HRESULT PUNK_ENGINE_API InitCaptureGraphBuilder(
		IGraphBuilder **ppGraph,  // Receives the pointer.
		ICaptureGraphBuilder2 **ppBuild  // Receives the pointer.
		);

	HRESULT PUNK_ENGINE_API EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);
	void PUNK_ENGINE_API DisplayDeviceInformation(IEnumMoniker *pEnum);

	//void PUNK_ENGINE_API PreviewStart();
	//void PUNK_ENGINE_API PreviewStop();
	//void PUNK_ENGINE_API DisplaySettings();
	//void PUNK_ENGINE_API Update();
	//void PUNK_ENGINE_API CreateCaptureWindow(int width, int height);
	//void PUNK_ENGINE_API CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);
	//void PUNK_ENGINE_API EnumerateCaptureDevices();
}

#endif	//	_H_PUNK_SYSTEM_CAMERA_CAPTURE_WIN32

#endif
