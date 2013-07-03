#ifndef _H_PUNK_OPENGL_ERROR_CHECK
#define _H_PUNK_OPENGL_ERROR_CHECK

namespace System { class string; }

#ifdef _DEBUG
#define GL_CALL(X) X; ValidateOpenGL(#X)
#else
#define GL_CALL(X) X;
#endif

namespace GPU
{
	namespace OpenGL
	{
		extern void ValidateOpenGL(const System::string& msg);
	}
}

#endif	//	_H_PUNK_OPENGL_ERROR_CHECK
