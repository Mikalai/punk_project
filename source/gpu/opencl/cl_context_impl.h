#ifndef _H_PUNK_OPENCL_CONTEXT_IMPL
#define _H_PUNK_OPENCL_CONTEXT_IMPL

#ifdef USE_OPENCL
#include <CL/opencl.h>
#include "errors/module.h"
#include "cl_context.h"
#endif

namespace GPU
{
	namespace OpenCL
	{
	    #ifdef USE_OPENCL
		struct ContextImpl
		{
			cl_context m_context;

			ContextImpl() : m_context(0) {}

			bool Init(cl_device_id device)
			{
				Clear();
				cl_int error;
				m_context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &error);
				CHECK_CL_ERROR(error, L"Can't create OpenCL context");
				return true;
			}

			bool Clear()
			{
				if (m_context)
				{
					cl_int error = clReleaseContext(m_context);
					CHECK_CL_ERROR(error, L"Can't release OpenCL context");
				}
				return true;
			}

			~ContextImpl()
			{
				Clear();
			}
		};
		#endif  //  USE_OPENCL
	}
}

#endif	//	_H_PUNK_OPENCL_CONTEXT_IMPL
