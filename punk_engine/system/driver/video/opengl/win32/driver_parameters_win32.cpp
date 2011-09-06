#ifdef _WIN32

#include "driver_parameters_win32.h"

namespace Driver
{
	DriverParameters DriverParameters::Create(System::Window* win, bool isFull)
	{
		DriverParameters p;
		p.window = *win;
		p.deviceContext = NULL;
		p.openglContext = NULL;
		p.width = 800;
		p.height = 600;
		p.bitsPerPixel = 32;
		p.refreshRate = 85;
		p.zNear = 0.01f;
		p.zFar = 1000.0f;
		p.fullScreen = isFull;
		return p;
	}
}

#endif
