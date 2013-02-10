#ifndef _H_PUNK_SYSTEM_CAMERA_CAPTURE_WIN32
#define _H_PUNK_SYSTEM_CAMERA_CAPTURE_WIN32

#include "../../config.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <dshow.h>

namespace GPU
{
	namespace OpenGL
	{
		class Texture2D;
	}
}

namespace System
{
	void PUNK_ENGINE SetCriticalSection(CRITICAL_SECTION* cs);
	void PUNK_ENGINE SetTexture(void* buffer, int* len);

	void PUNK_ENGINE TestCamera();

	HRESULT PUNK_ENGINE InitCaptureGraphBuilder(
		IGraphBuilder **ppGraph,  // Receives the pointer.
		ICaptureGraphBuilder2 **ppBuild  // Receives the pointer.
		);

	HRESULT PUNK_ENGINE EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);
	void PUNK_ENGINE DisplayDeviceInformation(IEnumMoniker *pEnum);

	//void PUNK_ENGINE PreviewStart();
	//void PUNK_ENGINE PreviewStop();
	//void PUNK_ENGINE DisplaySettings();
	//void PUNK_ENGINE Update();
	//void PUNK_ENGINE CreateCaptureWindow(int width, int height);
	//void PUNK_ENGINE CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);
	//void PUNK_ENGINE EnumerateCaptureDevices();
}

#endif	//	_H_PUNK_SYSTEM_CAMERA_CAPTURE_WIN32