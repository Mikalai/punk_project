#ifndef GL_BLENDING_H
#define GL_BLENDING_H

#include "../../common/blending/module.h"
#include "extensions.h"

namespace Gpu
{
	namespace OpenGL
	{
		GLenum BlendFunctionToOpenGL(BlendFunction value);
	}
}

#endif // GL_BLENDING_H
