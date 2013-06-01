#ifndef _H_PUNK_CUDA_YUY2_TO_RGB
#define _H_PUNK_CUDA_YUY2_TO_RGB

#include "../../config.h"

namespace ImageModule
{
	extern PUNK_ENGINE_PUBLIC bool YUY2toRGB(const unsigned char* src, int length, unsigned char* dst, int* out_length);
}

#endif