#ifndef _H_GPU_H
#define _H_GPU_H

#include "common/module.h"
#include "opengl/module.h"
#include "opencl/module.h"
#include "painter/module.h"
#include "gpu_config.h"

namespace GPU
{
	extern bool PUNK_ENGINE_PUBLIC GPU_INIT(const Config& data);	
	extern bool PUNK_ENGINE_PUBLIC GPU_DESTROY();	
}

#endif	//	_H_GPU_H
