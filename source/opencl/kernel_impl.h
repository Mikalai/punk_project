#ifndef _H_PUNK_OPENCL_KERNEL_IMPL
#define _H_PUNK_OPENCL_KERNEL_IMPL

#include "CL/opencl.h"
#include "kernel.h"
#include "../system/logger.h"
#include "../math/functions.h"
#include "buffer_impl.h"

namespace OpenCL
{
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
				if (error != CL_SUCCESS)
					return (out_error() << "Can't release kernel" << std::endl, false);
			}
			return true;
		}

		bool Call(int elements_to_process)
		{
			size_t local_size = 256;
			size_t global_size = Math::round_up((size_t)elements_to_process, local_size);
			cl_int error = clEnqueueNDRangeKernel(m_queue, m_kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
			if (error != CL_SUCCESS)
				return (out_error() << "Can't execute kernel" << std::endl, false);
			return true;
		}

		bool SetArgument(int index, int value)
		{
			cl_int error = clSetKernelArg(m_kernel, index, sizeof(cl_int), (void*)&value);
			if (error != CL_SUCCESS)
				return (out_error() << "Can't set integer element at " << index << " in kernel" << std::endl, false);
			return true;
		}

		bool SetArgument(int index, Buffer& buffer)
		{
			cl_int error = clSetKernelArg(m_kernel, index, sizeof(cl_mem), (void*)&(buffer.m_impl->m_buffer));
			if (error != CL_SUCCESS)
				return (out_error() << "Can't set buffer element at " << index << " in kernel" << std::endl, false);
			return true;
		}

		~KernelImpl()
		{
			Clear();
		}
	};
}

#endif