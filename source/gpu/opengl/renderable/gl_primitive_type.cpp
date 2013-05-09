#include "gl_primitive_type.h"
#include "../error/module.h"

namespace GPU
{
	namespace OpenGL
	{
		GLenum PrimitiveTypeToOpenGL(PrimitiveType type)
		{
			switch (type)
			{
			case GPU::PrimitiveType::POINTS:
				return GL_POINTS;
			case GPU::PrimitiveType::LINE_STRIP:
				return GL_LINE_STRIP;
			case GPU::PrimitiveType::LINE_LOOP:
				return GL_LINE_LOOP;
			case GPU::PrimitiveType::LINES:
				return GL_LINES;
			case GPU::PrimitiveType::LINE_STRIP_ADJANCECY:
				return GL_LINE_STRIP_ADJACENCY;
			case GPU::PrimitiveType::LINES_ADJANCENCY:
				return GL_LINES_ADJACENCY;
			case GPU::PrimitiveType::TRIANGLE_STRIP:
				return GL_TRIANGLE_STRIP;
			case GPU::PrimitiveType::TRIANGLE_FAN:
				return GL_TRIANGLE_FAN;
			case GPU::PrimitiveType::TRIANGLES:
				return GL_TRIANGLES;
			case GPU::PrimitiveType::TRIANGLE_STRIP_ADJANCECY:
				return GL_TRIANGLE_STRIP_ADJACENCY;
			case GPU::PrimitiveType::TRIANGLES_ADJANCECY:
				return GL_TRIANGLES_ADJACENCY;
			case GPU::PrimitiveType::QUADS:	//	if QUADS are used, they should be internally converted to triangles
				return GL_TRIANGLES;
			default:
				throw OpenGLException(L"Unsupported primitive type");
			}
		}
	}
}
