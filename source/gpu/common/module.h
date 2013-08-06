#ifndef _H_PUNK_GPU_COMMON_MODULE
#define _H_PUNK_GPU_COMMON_MODULE

#include "vertex.h"
#include "vertex_component.h"
#include "abstract_render_context_policy.h"
#include "renderable.h"
#include "gpu_state.h"
#include "../gpu_config.h"
#include "frame.h"
#include "video_driver.h"
#include "renderable_builder.h"
#include "primitive_type.h"
#include "render_batch.h"
#include "render_pass.h"
#include "primitives/module.h"
#include "frame_buffer/module.h"
#include "texture/module.h"

namespace Gpu
{
    extern bool PUNK_ENGINE_API GPU_COMMON_INIT(const Config& data);
}

#endif	//	_H_PUNK_GPU_COMMON_MODULE
