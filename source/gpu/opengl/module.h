#ifndef _H_PUNK_OPENGL_DRIVER_MODULE
#define _H_PUNK_OPENGL_DRIVER_MODULE

#include "buffers/module.h"
#include "driver/module.h"
#include "error/module.h"
#include "gl/module.h"
#include "renderable/module.h"
#include "textures/module.h"
#include "render_context/module.h"
#include "render_targets/module.h"
#include "../gpu_config.h"
#include "painter/module.h"

namespace Gpu
{
	namespace OpenGL
	{
		extern bool PUNK_ENGINE_API GPU_OPENGL_INIT(const Config& data);
		extern bool PUNK_ENGINE_API GPU_OPENGL_DESTROY();	
	}
}

#endif	//	_H_PUNK_OPENGL_DRIVER_MODULE
