#ifndef DRIVERPARAMETERS_OPENGL_H
#define DRIVERPARAMETERS_OPENGL_H

#ifdef __linux__
#include <unistd.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <gl3/gl3.h>
#include <GL/glx.h>
#include <gl3/glxext.h>
#endif

namespace System
{
    class Window;
}

namespace Driver
{
    namespace Video
    {
        namespace OpenGL
        {

            struct DriverParameters
            {
                Display* display;
                Window window;
                XVisualInfo* videoInfo;
                Colormap colorMap;
                XSetWindowAttributes setWindowAttributes;
                XEvent event;
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
    }
}

#endif // DRIVERPARAMETERS_OPENGL_H
