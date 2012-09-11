#ifndef DRIVER_PARAMETERS_WIN32_H
#define DRIVER_PARAMETERS_WIN32_H

#include "../../../../window.h"

namespace Driver
{
	struct DriverParameters
	{
		HWND window;
		HDC deviceContext;
		HGLRC openglContext;
		unsigned width;
		unsigned height;
		unsigned bitsPerPixel;
		unsigned refreshRate;
		float zNear;
		float zFar;
		bool fullScreen;
		static DriverParameters Create(System::Window* win, bool isFull = false);
	};
}

#endif // DRIVER_PARAMETERS_WIN32_H
