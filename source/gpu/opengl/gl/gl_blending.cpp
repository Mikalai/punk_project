#include "gl_blending.h"

namespace Gpu
{
	namespace OpenGL
	{
		GLenum BlendFunctionToOpenGL(BlendFunction value)
		{
			switch (value)
			{
			case BlendFunction::One:
				return GL_ONE;
			case BlendFunction::SourceAlpha:
				return GL_SRC_ALPHA;
			case BlendFunction::OneMinusSrcAlpha:
				return GL_ONE_MINUS_SRC_ALPHA;
			default:
				throw System::PunkException(L"Invalid blend function");
			}
		}
	}
}
