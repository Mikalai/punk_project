#ifndef _H_PUNK_OPENGL_DRIVER
#define _H_PUNK_OPENGL_DRIVER

#ifdef _WIN32

#ifdef PUNK_OPENGL_DRIVER_EXPORTS
#define MODULE_OPENGL __declspec(dllexport)
#else
#define MODULE_OPENGL __declspec(dllimport)
#endif

#include <windows.h>
#include "gl/gl3.h"
#include "gl/glext.h"
#include "gl/wglext.h"
#endif

#ifdef __linux__
#define PUNK_OPENGL_EXPORT
#endif

#endif