#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glext.h>

#ifdef _WIN32
#include <GL/wglext.h>
#endif

extern PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
extern PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
extern PFNGLFOGCOORDDEXTPROC glFogCoordfEXT;
extern PFNGLFOGCOORDFEXTPROC glFogCoorddEXT;
extern PFNGLFOGCOORDDVEXTPROC glFogCoorddvEXT;
extern PFNGLFOGCOORDFVEXTPROC glFogCoordfvEXT;
extern PFNGLFOGCOORDPOINTEREXTPROC glFogCoordPointerEXT;

namespace Extensions
{
extern void InitExtensions();
}