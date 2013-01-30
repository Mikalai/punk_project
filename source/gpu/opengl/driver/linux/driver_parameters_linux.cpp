#ifdef __linux__

#include "driver_parameters_linux.h"
#include "../../../../system/window.h"

namespace Driver
{
    namespace Video
    {
        namespace OpenGL
        {
            DriverParameters DriverParameters::Create(System::Window* win, bool isFull)
            {
                DriverParameters p;
                p.display = win->GetDisplay();
                p.window = win->GetWindow();
                p.colorMap = *win->GetColorMap();
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
    }
}

#endif
