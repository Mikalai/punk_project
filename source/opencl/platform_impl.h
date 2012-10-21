#ifndef _H_PUNK_OPENCL_PLATFORM_IMPL
#define _H_PUNK_OPENCL_PLATFORM_IMPL

#include <CL/opencl.h>
#include "../system/logger.h"
#include "platform.h"

namespace OpenCL
{
	struct Platform::PlatformImpl
	{
		cl_platform_id m_platform;

		PlatformImpl() : m_platform(0) {}

		bool Init()
		{
			Clear();
			cl_int res = clGetPlatformIDs(1, &m_platform, nullptr);
			if (res != CL_SUCCESS)
				return (out_error() << "Can't get OpenCL platform id" << std::endl, false);
			return true;
		}

		bool Clear()
		{
			m_platform = 0;
			return true;
		}

		~PlatformImpl()
		{
			Clear();
		}
	};
}

#endif