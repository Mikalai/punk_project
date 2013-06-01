
// ATTENTION: under construction

#ifndef _H_PUNK_SYSTEM_CAMERA_CAPTURE
#define _H_PUNK_SYSTEM_CAMERA_CAPTURE

#include "../../config.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <dshow.h>

namespace GPU
{
		class Texture2D;
}

namespace System
{
	void PUNK_ENGINE_PUBLIC SetCriticalSection(CRITICAL_SECTION* cs);
	void PUNK_ENGINE_PUBLIC SetTexture(void* buffer, int* len);

	void PUNK_ENGINE_PUBLIC TestCamera();

	HRESULT PUNK_ENGINE_PUBLIC InitCaptureGraphBuilder(
		IGraphBuilder **ppGraph,  // Receives the pointer.
		ICaptureGraphBuilder2 **ppBuild  // Receives the pointer.
		);

	HRESULT PUNK_ENGINE_PUBLIC EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);
	void PUNK_ENGINE_PUBLIC DisplayDeviceInformation(IEnumMoniker *pEnum);

	//void PUNK_ENGINE_PUBLIC PreviewStart();
	//void PUNK_ENGINE_PUBLIC PreviewStop();
	//void PUNK_ENGINE_PUBLIC DisplaySettings();
	//void PUNK_ENGINE_PUBLIC Update();
	//void PUNK_ENGINE_PUBLIC CreateCaptureWindow(int width, int height);
	//void PUNK_ENGINE_PUBLIC CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);
	//void PUNK_ENGINE_PUBLIC EnumerateCaptureDevices();
}

#endif	//	_H_PUNK_SYSTEM_CAMERA_CAPTURE_WIN32