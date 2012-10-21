#ifndef _H_PUNK_OPENCL_CONTEXT_IMPL
#define _H_PUNK_OPENCL_CONTEXT_IMPL

#include <CL/opencl.h>
#include "../system/logger.h"
#include "context.h"

namespace OpenCL
{
	struct Context::ContextImpl
	{
		cl_context m_context;

		ContextImpl() : m_context(0) {}

		bool Init(cl_device_id device)
		{
			Clear();
			cl_int error;
			m_context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &error);
			if (error != CL_SUCCESS)
				return (out_error() << "Can't create OpenCL context" << std::endl, false);
			return true;
		}

		bool Clear()
		{
			if (m_context)
			{
				cl_int error = clReleaseContext(m_context);
				if (error != CL_SUCCESS)
					return (out_error() << "Can't release OpenCL context" 
							<< std::endl, false);
			}
			return true;
		}

		~ContextImpl()
		{
			Clear();
		}
	};
}

#endif	//	_H_PUNK_OPENCL_CONTEXT_IMPL