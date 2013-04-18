#ifndef _H_PUNK_OPENCL_KERNEL_IMPL
#define _H_PUNK_OPENCL_KERNEL_IMPL

#ifdef USE_OPENCL
#include "CL/opencl.h"
#include "errors/module.h"
#include "cl_kernel.h"
#include "../../math/helper.h"
#include "cl_buffer_impl.h"
#endif

namespace GPU
{
	namespace OpenCL
	{
	    #ifdef USE_OPENCL
		struct Kernel::KernelImpl
		{
			cl_kernel m_kernel;
			cl_command_queue m_queue;

			KernelImpl() : m_kernel(0), m_queue(0) {}

			bool Clear()
			{
				if (m_kernel)
				{
					cl_int error = clReleaseKernel(m_kernel);
					CHECK_CL_ERROR(error, L"Can't release kernel");
				}
				return true;
			}

			bool Call(int elements_to_process)
			{
				size_t local_size = 256;
				size_t global_size = Math::RoundUp((size_t)elements_to_process, local_size);
				cl_int error = clEnqueueNDRangeKernel(m_queue, m_kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
				CHECK_CL_ERROR(error, L"Can't execute kernel");
				return true;
			}

			bool SetArgument(int index, int value)
			{
				cl_int error = clSetKernelArg(m_kernel, index, sizeof(cl_int), (void*)&value);
				CHECK_CL_ERROR(error, L"Can't set integer element at " + System::string::Convert(index) + L" in kernel");
				return true;
			}

			bool SetArgument(int index, Buffer& buffer)
			{
				cl_int error = clSetKernelArg(m_kernel, index, sizeof(cl_mem), (void*)&(buffer.m_impl->m_buffer));
				CHECK_CL_ERROR(error, L"Can't set buffer element at " + System::string::Convert(index) + L" in kernel");
				return true;
			}

			~KernelImpl()
			{
				Clear();
			}
		};

		#endif
	}
}

#endif
