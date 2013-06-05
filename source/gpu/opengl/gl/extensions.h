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

#define GLX_EXTENSION_NAME   "GLX"

/*
 * Tokens for glXChooseVisual and glXGetConfig:
 */
#define GLX_USE_GL		1
#define GLX_BUFFER_SIZE		2
#define GLX_LEVEL		3
#define GLX_RGBA		4
#define GLX_DOUBLEBUFFER	5
#define GLX_STEREO		6
#define GLX_AUX_BUFFERS		7
#define GLX_RED_SIZE		8
#define GLX_GREEN_SIZE		9
#define GLX_BLUE_SIZE		10
#define GLX_ALPHA_SIZE		11
#define GLX_DEPTH_SIZE		12
#define GLX_STENCIL_SIZE	13
#define GLX_ACCUM_RED_SIZE	14
#define GLX_ACCUM_GREEN_SIZE	15
#define GLX_ACCUM_BLUE_SIZE	16
#define GLX_ACCUM_ALPHA_SIZE	17


/*
 * Error codes returned by glXGetConfig:
 */
#define GLX_BAD_SCREEN		1
#define GLX_BAD_ATTRIBUTE	2
#define GLX_NO_EXTENSION	3
#define GLX_BAD_VISUAL		4
#define GLX_BAD_CONTEXT		5
#define GLX_BAD_VALUE       	6
#define GLX_BAD_ENUM		7


/*
 * GLX 1.1 and later:
 */
#define GLX_VENDOR		1
#define GLX_VERSION		2
#define GLX_EXTENSIONS 		3


/*
 * GLX 1.3 and later:
 */
#define GLX_CONFIG_CAVEAT		0x20
#define GLX_DONT_CARE			0xFFFFFFFF
#define GLX_X_VISUAL_TYPE		0x22
#define GLX_TRANSPARENT_TYPE		0x23
#define GLX_TRANSPARENT_INDEX_VALUE	0x24
#define GLX_TRANSPARENT_RED_VALUE	0x25
#define GLX_TRANSPARENT_GREEN_VALUE	0x26
#define GLX_TRANSPARENT_BLUE_VALUE	0x27
#define GLX_TRANSPARENT_ALPHA_VALUE	0x28
#define GLX_WINDOW_BIT			0x00000001
#define GLX_PIXMAP_BIT			0x00000002
#define GLX_PBUFFER_BIT			0x00000004
#define GLX_AUX_BUFFERS_BIT		0x00000010
#define GLX_FRONT_LEFT_BUFFER_BIT	0x00000001
#define GLX_FRONT_RIGHT_BUFFER_BIT	0x00000002
#define GLX_BACK_LEFT_BUFFER_BIT	0x00000004
#define GLX_BACK_RIGHT_BUFFER_BIT	0x00000008
#define GLX_DEPTH_BUFFER_BIT		0x00000020
#define GLX_STENCIL_BUFFER_BIT		0x00000040
#define GLX_ACCUM_BUFFER_BIT		0x00000080
#define GLX_NONE			0x8000
#define GLX_SLOW_CONFIG			0x8001
#define GLX_TRUE_COLOR			0x8002
#define GLX_DIRECT_COLOR		0x8003
#define GLX_PSEUDO_COLOR		0x8004
#define GLX_STATIC_COLOR		0x8005
#define GLX_GRAY_SCALE			0x8006
#define GLX_STATIC_GRAY			0x8007
#define GLX_TRANSPARENT_RGB		0x8008
#define GLX_TRANSPARENT_INDEX		0x8009
#define GLX_VISUAL_ID			0x800B
#define GLX_SCREEN			0x800C
#define GLX_NON_CONFORMANT_CONFIG	0x800D
#define GLX_DRAWABLE_TYPE		0x8010
#define GLX_RENDER_TYPE			0x8011
#define GLX_X_RENDERABLE		0x8012
#define GLX_FBCONFIG_ID			0x8013
#define GLX_RGBA_TYPE			0x8014
#define GLX_COLOR_INDEX_TYPE		0x8015
#define GLX_MAX_PBUFFER_WIDTH		0x8016
#define GLX_MAX_PBUFFER_HEIGHT		0x8017
#define GLX_MAX_PBUFFER_PIXELS		0x8018
#define GLX_PRESERVED_CONTENTS		0x801B
#define GLX_LARGEST_PBUFFER		0x801C
#define GLX_WIDTH			0x801D
#define GLX_HEIGHT			0x801E
#define GLX_EVENT_MASK			0x801F
#define GLX_DAMAGED			0x8020
#define GLX_SAVED			0x8021
#define GLX_WINDOW			0x8022
#define GLX_PBUFFER			0x8023
#define GLX_PBUFFER_HEIGHT              0x8040
#define GLX_PBUFFER_WIDTH               0x8041
#define GLX_RGBA_BIT			0x00000001
#define GLX_COLOR_INDEX_BIT		0x00000002
#define GLX_PBUFFER_CLOBBER_MASK	0x08000000


/*
 * GLX 1.4 and later:
 */
#define GLX_SAMPLE_BUFFERS              0x186a0 /*100000*/
#define GLX_SAMPLES                     0x186a1 /*100001*/



typedef struct __GLXcontextRec *GLXContext;
typedef XID GLXPixmap;
typedef XID GLXDrawable;
/* GLX 1.3 and later */
typedef struct __GLXFBConfigRec *GLXFBConfig;
typedef XID GLXFBConfigID;
typedef XID GLXContextID;
typedef XID GLXWindow;
typedef XID GLXPbuffer;


/*
** Events.
** __GLX_NUMBER_EVENTS is set to 17 to account for the BufferClobberSGIX
**  event - this helps initialization if the server supports the pbuffer
**  extension and the client doesn't.
*/
#define GLX_PbufferClobber	0
#define GLX_BufferSwapComplete	1

#define __GLX_NUMBER_EVENTS 17
typedef struct __GLXcontextRec *GLXContext;
typedef XID GLXPbuffer;
typedef XID GLXPixmap;
typedef XID GLXWindow;
typedef struct __GLXFBConfigRec *GLXFBConfig;
typedef XID GLXDrawable;
typedef XID GLXContextID;

typedef Bool (*PFNGLXQUERYVERSIONPROC)( Display *dpy, int *maj, int *min );
typedef const char* (*PFNGLXQUERYEXTENSIONSSTRINGPROC)( Display *dpy, int screen );
typedef GLXContext (*PFNGLXCREATECONTEXTPROC)( Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct );
typedef Bool (*PFNGLXISDIRECTPROC)( Display *dpy, GLXContext ctx );
typedef Bool (*PFNGLXMAKECURRENTPROX)( Display *dpy, GLXDrawable drawable, GLXContext ctx);
//#include <../GL/glx.h>
#include "../gl/glxext.h"
#endif

#include "../error/module.h"

namespace GPU
{
	class VideoDriver;
	namespace OpenGL
	{

#ifdef _WIN32
    extern PUNK_ENGINE_LOCAL PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionStringARB;
    extern PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
#elif defined __gnu_linux__
        extern PFNGLXGETPROCADDRESSPROC glXGetProcAddress;
        extern PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
        extern PFNGLXQUERYVERSIONPROC glXQueryVersion;
        extern PFNGLXCHOOSEFBCONFIGPROC glXChooseFBConfig;
        extern PFNGLXGETVISUALFROMFBCONFIGPROC glXGetVisualFromFBConfig;
        extern PFNGLXGETFBCONFIGATTRIBPROC glXGetFBConfigAttrib;
        extern PFNGLXQUERYEXTENSIONSSTRINGPROC glXQueryExtensionsString;
        extern PFNGLXCREATECONTEXTPROC glXCreateContext;
        extern PFNGLXCREATENEWCONTEXTPROC glXCreateNewContext;
        extern PFNGLXISDIRECTPROC glXIsDirect;
        extern PFNGLXMAKECURRENTPROX glXMakeCurrent;
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
		extern PFNGLVIEWPORTPROC glViewport;
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
	}
}

#endif //	_ENSIONS_H
