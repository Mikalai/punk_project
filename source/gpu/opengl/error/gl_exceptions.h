#ifndef _H_PUNK_OPENGL_EXCEPTIONS
#define _H_PUNK_OPENGL_EXCEPTIONS

#include "../../error/module.h"

namespace GPU
{
	namespace OpenGL
	{
		class PUNK_ENGINE_PUBLIC OpenGLException : public GPUException
		{
		public:
			OpenGLException();
			OpenGLException(const System::string& msg);
		};

		class PUNK_ENGINE_PUBLIC OpenGLNotImplemented: public OpenGLException
		{
		public:
			OpenGLNotImplemented() : OpenGLException(L"OpenGLNotImplemented") {}
			OpenGLNotImplemented(const System::string& msg) : OpenGLException(msg) {}
		};

		class PUNK_ENGINE_PUBLIC OpenGLInvalidEnumException : public OpenGLException
		{
		public:
			OpenGLInvalidEnumException() : OpenGLException(L"OpenGLInvalidEnumException") {}
			OpenGLInvalidEnumException(const System::string& msg) : OpenGLException(msg) {}
		};

		class PUNK_ENGINE_PUBLIC OpenGLInvalidValueException : public OpenGLException
		{
		public:
			OpenGLInvalidValueException() : OpenGLException(L"OpenGLInvalidValueException") {}
			OpenGLInvalidValueException(const System::string& msg) : OpenGLException(msg) {}
		};

		class PUNK_ENGINE_PUBLIC OpenGLInvalidOperationException : public OpenGLException
		{
		public:
			OpenGLInvalidOperationException() : OpenGLException(L"OpenGLInvalidOperationException") {}
			OpenGLInvalidOperationException(const System::string& msg) : OpenGLException(msg) {}
		};
		
		class PUNK_ENGINE_PUBLIC OpenGLInvalidFrameBufferOperationException : public OpenGLException
		{
		public:
			OpenGLInvalidFrameBufferOperationException() : OpenGLException(L"OpenGLInvalidFrameBufferOperationException") {}
			OpenGLInvalidFrameBufferOperationException(const System::string& msg) : OpenGLException(msg) {}
		};

		class PUNK_ENGINE_PUBLIC OpenGLOutOfMemoryException : public OpenGLException
		{
		public:
			OpenGLOutOfMemoryException() : OpenGLException(L"OpenGLOutOfMemoryException") {}
			OpenGLOutOfMemoryException(const System::string& msg) : OpenGLException(msg) {}
		};
	}
}

#endif	//	_H_PUNK_OPENGL_EXCEPTIONS