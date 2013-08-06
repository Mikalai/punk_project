#include "gl_primitive_type.h"
#include "../error/module.h"

namespace Gpu
{
	namespace OpenGL
	{
		GLenum PrimitiveTypeToOpenGL(PrimitiveType type)
		{
			switch (type)
			{
			case Gpu::PrimitiveType::POINTS:
				return GL_POINTS;
			case Gpu::PrimitiveType::LINE_STRIP:
				return GL_LINE_STRIP;
			case Gpu::PrimitiveType::LINE_LOOP:
				return GL_LINE_LOOP;
			case Gpu::PrimitiveType::LINES:
				return GL_LINES;
			case Gpu::PrimitiveType::LINE_STRIP_ADJANCECY:
				return GL_LINE_STRIP_ADJACENCY;
			case Gpu::PrimitiveType::LINES_ADJANCENCY:
				return GL_LINES_ADJACENCY;
			case Gpu::PrimitiveType::TRIANGLE_STRIP:
				return GL_TRIANGLE_STRIP;
			case Gpu::PrimitiveType::TRIANGLE_FAN:
				return GL_TRIANGLE_FAN;
			case Gpu::PrimitiveType::TRIANGLES:
				return GL_TRIANGLES;
			case Gpu::PrimitiveType::TRIANGLE_STRIP_ADJANCECY:
				return GL_TRIANGLE_STRIP_ADJACENCY;
			case Gpu::PrimitiveType::TRIANGLES_ADJANCECY:
				return GL_TRIANGLES_ADJACENCY;
			case Gpu::PrimitiveType::QUADS:	//	if QUADS are used, they should be internally converted to triangles
				return GL_TRIANGLES;
			default:
				throw OpenGLException(L"Unsupported primitive type");
			}
		}
	}
}
