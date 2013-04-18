#include "gl_exceptions.h"
#include "../gl/module.h"

#include "gl_error_check.h"

namespace GPU
{
	namespace OpenGL
	{
		void ValidateOpenGL(const System::string& msg)
		{
#ifdef _DEBUG
			GLenum error = glGetError();
			switch(error)
			{
			case GL_NO_ERROR: break;
			case GL_INVALID_ENUM: throw OpenGLInvalidEnumException(msg);
			case GL_INVALID_VALUE: throw OpenGLInvalidValueException(msg);
			case GL_INVALID_OPERATION: throw OpenGLInvalidOperationException(msg);
			case GL_INVALID_FRAMEBUFFER_OPERATION: throw OpenGLInvalidFrameBufferOperationException(msg);
			case GL_OUT_OF_MEMORY: throw OpenGLOutOfMemoryException(msg);
			default: throw OpenGLException(msg);
			};
#endif	//	_DEBUG
		}
	}
}
