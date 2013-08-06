/*
File: Extensions.h
Author: Abramau Mikalaj
Description: Contains declarations of OpenGL extension functions
*/

#ifndef _PUNK_EXTENSIONS
#define _PUNK_EXTENSIONS

#include "../../../config.h"

#include "glcorearb.h"

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include "wglext.h"
#elif defined __gnu_linux__
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xutil.h>
#include <X11/extensions/xf86vmode.h>
#include <../GL/glx.h>
#include "../gl/glxext.h"
#endif

#include "../error/module.h"

namespace Gpu
{
	class VideoDriver;
	namespace OpenGL
	{

#ifdef _WIN32
    extern PUNK_ENGINE_LOCAL PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionStringARB;
    extern PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
#elif defined __gnu_linux__
        extern PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
//        extern PFNGLXCHOOSEFBCONFIGPROC glXChooseFBConfig;
//        extern PFNGLXGETVISUALFROMFBCONFIGPROC glXGetVisualFromFBConfig;
//        extern PFNGLXGETFBCONFIGATTRIBPROC glXGetFBConfigAttrib;
//        extern PFNGLXCREATENEWCONTEXTPROC glXCreateNewContext;
//        extern PFNGLXGETFBCONFIGSPROC glXGetFBConfigs;
#endif

		extern PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v;
		extern PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv;
		extern PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameterui64v;
		extern PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv;
		extern PFNGLTEXPARAMETERFPROC glTexParameterf;
		extern PFNGLBINDTEXTUREPROC glBindTexture;
		extern PFNGLGETINTEGERVPROC glGetIntegerv;
		extern PFNGLPIXELSTOREIPROC glPixelStorei;
		extern PFNGLPIXELSTOREFPROC glPixelStoref;
		extern PFNGLBLENDCOLORPROC glBlendColor;
		extern PFNGLBLENDEQUATIONPROC glBlendEquation;
		extern PFNGLBLENDEQUATIONIPROC glBlendEquationi;
		extern PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;
		extern PFNGLBLENDEQUATIONSEPARATEIPROC glBlendEquationSeparatei;
		extern PFNGLENABLEIPROC glEnablei;
		extern PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
		extern PFNGLBLENDFUNCPROC glBlendFunc;
		extern PFNGLBLENDFUNCIPROC glBlendFunci;
		extern PFNGLACTIVETEXTUREPROC glActiveTexture;
		extern PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
        extern PFNGLBUFFERDATAPROC glBufferData;
        extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
		extern PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData;
		extern PFNGLGENBUFFERSPROC glGenBuffers;
		extern PFNGLBINDBUFFERPROC glBindBuffer;
		extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
		extern PFNGLMAPBUFFERPROC glMapBuffer;
		extern PFNGLUNMAPBUFFERPROC glUnmapBuffer;
		extern PFNGLISBUFFERPROC glIsBuffer;
		extern PFNGLISRENDERBUFFERPROC glIsRenderbuffer;
		extern PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
		extern PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
		extern PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
		extern PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
		extern PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv;
		extern PFNGLISFRAMEBUFFERPROC glIsFramebuffer;
		extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
		extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
		extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
		extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
		extern PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture1D;
		extern PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
		extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv;
		extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
		extern PFNGLCREATESHADERPROC glCreateShader;
		extern PFNGLCREATEPROGRAMPROC glCreateProgram;
		extern PFNGLDELETESHADERPROC glDeleteShader;
		extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
		extern PFNGLSHADERSOURCEPROC glShaderSource;
		extern PFNGLCOMPILESHADERPROC glCompileShader;
		extern PFNGLATTACHSHADERPROC glAttachShader;
		extern PFNGLDETACHSHADERPROC glDetachShader;
		extern PFNGLLINKPROGRAMPROC glLinkProgram;
		extern PFNGLUSEPROGRAMPROC glUseProgram;
		extern PFNGLVALIDATEPROGRAMPROC glValidateProgram;
		extern PFNGLUNIFORM1FPROC glUniform1f;
		extern PFNGLUNIFORM1FVPROC glUniform1fv;
		extern PFNGLUNIFORM1IPROC glUniform1i;
		extern PFNGLUNIFORM1IVPROC glUniform1iv;
		extern PFNGLUNIFORM2FPROC glUniform2f;
		extern PFNGLUNIFORM2FVPROC glUniform2fv;
		extern PFNGLUNIFORM2IVPROC glUniform2iv;
		extern PFNGLUNIFORM3FPROC glUniform3f;
		extern PFNGLUNIFORM3IVPROC glUniform3iv;
		extern PFNGLUNIFORM3FVPROC glUniform3fv;
		extern PFNGLUNIFORM3IPROC glUniform3i;
		extern PFNGLUNIFORM4FPROC glUniform4f;
		extern PFNGLUNIFORM4IVPROC glUniform4iv;
		extern PFNGLUNIFORM4FVPROC glUniform4fv;
		extern PFNGLUNIFORM4IPROC glUniform4i;
		extern PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
		extern PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
		extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
		extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
		extern PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders;
		extern PFNGLGETSHADERSOURCEPROC glGetShaderSource;
		extern PFNGLGETUNIFORMFVPROC glGetUniformfv;
		extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
		extern PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d;
		extern PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv;
		extern PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
		extern PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;
		extern PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s;
		extern PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv;
		extern PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d;
		extern PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv;
		extern PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;
		extern PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;
		extern PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s;
		extern PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv;

		extern PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d;
		extern PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv;
		extern PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;
		extern PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;
		extern PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s;
		extern PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv;

		extern PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d;
		extern PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv;
		extern PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f;
		extern PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
		extern PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s;
		extern PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv;

		extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
		extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
		extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
		extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
		extern PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv;
		extern PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv;
		extern PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv;
		extern PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv;
		extern PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;

		extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;

		extern PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements;
		extern PFNGLGETSTRINGIPROC glGetStringi;/**/
		extern PFNGLGETERRORPROC glGetError;
		extern PFNGLGETINTEGERVPROC glGetIntegerv;
        //extern PFNGLVIEWPORTPROC glViewport;
		extern PFNGLCLEARCOLORPROC glClearColor;
		extern PFNGLCLEARDEPTHFPROC glClearDepthf;
		extern PFNGLCLEARDEPTHPROC glClearDepth;
		extern PFNGLENABLEPROC glEnable;
		extern PFNGLDISABLEPROC glDisable;
		extern PFNGLREADPIXELSPROC glReadPixels;
		extern PFNGLGETSTRINGPROC glGetString;
		extern PFNGLGENTEXTURESPROC glGenTextures;
		extern PFNGLBINDTEXTUREPROC glBindTexture;
		extern PFNGLTEXPARAMETERFPROC glTexParameterf;
		extern PFNGLTEXPARAMETERIPROC glTexParameteri;
		extern PFNGLTEXPARAMETERFVPROC glTexParameterfv;
		extern PFNGLTEXIMAGE2DPROC glTexImage2D;
		extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
		extern PFNGLDELETETEXTURESPROC glDeleteTextures;
		extern PFNGLDRAWBUFFERPROC glDrawBuffer;
		extern PFNGLREADBUFFERPROC glReadBuffer;
		extern PFNGLGETSHADERIVPROC glGetShaderiv;
		extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
		extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
		extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
		extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
		extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
		extern PFNGLDRAWARRAYSPROC glDrawArrays;
		extern PFNGLDRAWARRAYSINDIRECTPROC glDrawArraysIndirect;
		extern PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced;
		extern PFNGLDRAWELEMENTSPROC glDrawElements;
		extern PFNGLDRAWELEMENTSINDIRECTPROC glDrawElementsIndirect;
		extern PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced;
        extern PUNK_ENGINE_API PFNGLCLEARPROC glClear;
		extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
		extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

		extern PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D;
		extern PFNGLPOLYGONMODEPROC glPolygonMode;

		extern PFNGLFENCESYNCPROC glFenceSync;
		extern PFNGLWAITSYNCPROC glWaitSync;
		extern PFNGLDELETESYNCPROC glDeleteSync;

		extern PFNGLDRAWBUFFERSPROC glDrawBuffers;

		extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample;
		extern PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;
		extern PFNGLDEPTHFUNCPROC glDepthFunc;
		extern PFNGLDEPTHMASKPROC glDepthMask;

		extern PFNGLPOINTSIZEPROC glPointSize;
		extern PFNGLPOINTPARAMETERIVPROC glPointParameteriv;
		extern PFNGLPOINTPARAMETERIPROC glPointParameteri;
		extern PFNGLPOINTPARAMETERFVPROC glPointParameterfv;
		extern PFNGLPOINTPARAMETERFPROC glPointParameterf;

		extern PFNGLCULLFACEPROC glCullFace;
		extern PFNGLLINEWIDTHPROC glLineWidth;

		extern PFNGLTEXTURESTORAGE1DEXTPROC glTextureStorage1DEXT;
		extern PFNGLTEXTURESTORAGE2DEXTPROC glTextureStorage2DEXT;

        extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC glRenderbufferStorageMultisampleCoverageNV;
	}
}

#endif //	_ENSIONS_H
