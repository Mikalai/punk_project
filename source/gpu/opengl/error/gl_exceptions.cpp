#include "gl_exceptions.h"

namespace GPU
{
	namespace OpenGL
	{
		OpenGLException::OpenGLException()
			: GPUException(L"OpenGLException")
		{}

			
		OpenGLException::OpenGLException(const System::string& msg)
			: GPUException(msg)
		{}
	}
}