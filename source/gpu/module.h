#ifndef _H_GPU_H
#define _H_GPU_H

#include "common/module.h"
//#include "opengl/module.h"
#include "opencl/module.h"
#include "painter/module.h"
#include "gpu_config.h"

namespace Gpu
{
    extern VideoDriver* Init(const VideoDriverDesc& data);
    extern void Destroy(VideoDriver* driver);
}

#endif	//	_H_GPU_H
