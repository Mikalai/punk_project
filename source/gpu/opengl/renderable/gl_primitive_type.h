#ifndef _H_PUNK_GPU_OPENGL_PRIMITVE_TYPE
#define _H_PUNK_GPU_OPENGL_PRIMITVE_TYPE

#include "../../common/primitive_type.h"
#include "../gl/module.h"

namespace Gpu
{
	namespace OpenGL
	{
		extern GLenum PrimitiveTypeToOpenGL(PrimitiveType type);
	}
}

#endif	//	_H_PUNK_GPU_OPENGL_PRIMITVE_TYPE