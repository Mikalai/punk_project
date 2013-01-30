#ifndef _H_PUNK_OPENGL_ERROR_CHECK
#define _H_PUNK_OPENGL_ERROR_CHECK

#include "gl_exceptions.h"
#include "../gl/glcorearb.h"

#ifdef _DEBUG
#define CHECK_GL_ERROR(X) { \
	GLenum error = glGetError();\
	switch(error)\
	{ \
	case GL_NO_ERROR: break;\
	case GL_INVALID_ENUM: throw OpenGLInvalidEnumException(X);\
	case GL_INVALID_VALUE: throw OpenGLInvalidValueException(X);\
	case GL_INVALID_OPERATION: throw OpenGLInvalidOperationException(X);\
	case GL_INVALID_FRAMEBUFFER_OPERATION: throw OpenGLInvalidFrameBufferOperationException(X);\
	case GL_OUT_OF_MEMORY: throw OpenGLOutOfMemoryException(X);\
	default: throw OpenGLException(X);\
	}; }
#else
#define CHECK_GL_ERROR(X);
#endif	_DEBUG

#endif	//	_H_PUNK_OPENGL_ERROR_CHECK