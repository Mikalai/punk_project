#ifndef _H_PUNK_OPENCL_PLATFORM_IMPL
#define _H_PUNK_OPENCL_PLATFORM_IMPL

#ifdef USE_OPENCL
#include <CL/opencl.h>
#include "errors/module.h"
#include "cl_platform.h"
#else
#include "cl_platform.h"
#endif

namespace GPU
{
	namespace OpenCL
	{
	    #ifdef USE_OPENCL
		struct Platform::PlatformImpl
		{
			cl_platform_id m_platform;

			PlatformImpl() : m_platform(0) {}

			bool Init()
			{
				Clear();
				cl_int res = clGetPlatformIDs(1, &m_platform, nullptr);
				CHECK_CL_ERROR(res, L"Can't get OpenCL platform id");
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
		#endif  //  USE_OPENCL
	}
}

#endif
