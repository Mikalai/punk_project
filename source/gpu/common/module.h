#ifndef _H_PUNK_GPU_COMMON_MODULE
#define _H_PUNK_GPU_COMMON_MODULE

#include "vertex.h"
#include "vertex_component.h"
#include "abstract_render_context_policy.h"
#include "renderable.h"
#include "gpu_state.h"
#include "render_target.h"
#include "../gpu_config.h"
#include "frame.h"
#include "video_driver.h"

namespace GPU
{
	extern bool PUNK_ENGINE GPU_COMMON_INIT(const Config& data);
}

#endif	//	_H_PUNK_GPU_COMMON_MODULE