#ifndef _H_PUNK_OPENCL_DEVICE_IMPL
#define _H_PUNK_OPENCL_DEVICE_IMPL

#ifdef USE_OPENCL
#include <CL/opencl.h>
#include "errors/module.h"
#include "cl_device.h"
#endif

namespace GPU
{
	namespace OpenCL
	{
	    #ifdef USE_OPENCL
		struct Device::DeviceImpl
		{
			cl_device_id m_device;

			DeviceImpl() : m_device(0) {}

			bool Init(cl_platform_id platform)
			{
				Clear();
				cl_int res = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &m_device, nullptr);
				CHECK_CL_ERROR(res, L"Can't get GPU device id");
				return true;
			}

			bool Clear()
			{
				m_device = 0;
				return true;
			}

			~DeviceImpl()
			{
				Clear();
			}
		};
		#endif
	}
}

#endif	//	_H_PUNK_OPENCL_DEVICE_IMPL
