#ifndef _H_PUNK_OPENGL_DRIVER_MODULE
#define _H_PUNK_OPENGL_DRIVER_MODULE

#include "buffers/module.h"
#include "driver/module.h"
#include "error/module.h"
#include "gl/module.h"
#include "renderable/module.h"
#include "textures/module.h"
#include "render_context/module.h"

namespace GPU
{
	namespace OpenGL
	{
		extern bool PUNK_ENGINE GPU_OPENGL_INIT(void* data);
	}
}

#endif	//	_H_PUNK_OPENGL_DRIVER_MODULE