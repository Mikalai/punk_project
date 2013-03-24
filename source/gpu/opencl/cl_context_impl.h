#ifndef _H_PUNK_OPENCL_CONTEXT_IMPL
#define _H_PUNK_OPENCL_CONTEXT_IMPL

#include <CL/opencl.h>
#include "errors/module.h"
#include "cl_context.h"

namespace GPU
{
	namespace OpenCL
	{
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
	}
}

#endif	//	_H_PUNK_OPENCL_CONTEXT_IMPL