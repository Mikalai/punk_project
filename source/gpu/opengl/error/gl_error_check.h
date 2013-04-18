#ifndef _H_PUNK_OPENGL_ERROR_CHECK
#define _H_PUNK_OPENGL_ERROR_CHECK

namespace System { class string; }

namespace GPU
{
	namespace OpenGL
	{
		extern void ValidateOpenGL(const System::string& msg);
	}
}

#endif	//	_H_PUNK_OPENGL_ERROR_CHECK