#include "Extensions.h"

PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
PFNGLFOGCOORDDEXTPROC glFogCoordfEXT;
PFNGLFOGCOORDFEXTPROC glFogCoorddEXT;
PFNGLFOGCOORDDVEXTPROC glFogCoorddvEXT;
PFNGLFOGCOORDFVEXTPROC glFogCoordfvEXT;
PFNGLFOGCOORDPOINTEREXTPROC glFogCoordPointerEXT;

namespace Extensions
{
	void* GetProcAddress(const char* name)
	{
#ifdef _WIN32
		return wglGetProcAddress(name);
#endif
	}

	void InitExtensions()
	{
		glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)GetProcAddress("glActiveTextureARB");
		glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)GetProcAddress("glClientActiveTextureARB");
		glFogCoordfEXT = (PFNGLFOGCOORDDEXTPROC)GetProcAddress("glFogCoordfEXT");
		glFogCoorddEXT = (PFNGLFOGCOORDFEXTPROC)GetProcAddress("glFogCoorddEXT");
		glFogCoorddvEXT = (PFNGLFOGCOORDDVEXTPROC)GetProcAddress("glFogCoorddvEXT");
		glFogCoordfvEXT = (PFNGLFOGCOORDFVEXTPROC)GetProcAddress("glFogCoordfvEXT");
		glFogCoordPointerEXT = (PFNGLFOGCOORDPOINTEREXTPROC)GetProcAddress("glFogCoordPointerEXT");
	}
}