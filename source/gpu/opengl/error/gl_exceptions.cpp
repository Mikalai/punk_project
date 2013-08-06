#include "gl_exceptions.h"

namespace Gpu
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