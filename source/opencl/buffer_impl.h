#ifndef _H_PUNK_OPENCL_BUFFER_IMPL
#define _H_PUNK_OPENCL_BUFFER_IMPL

#include <CL/opencl.h>
#include "../system/logger.h"
#include "buffer.h"

namespace OpenCL
{
	struct Buffer::BufferImpl
	{
		cl_mem m_buffer;
		cl_command_queue m_queue;
		//cl_mem_flags m_flags;
		//cl_context m_context;

		BufferImpl() : m_buffer(0) {}
		
		~BufferImpl()
		{
			Clear();
		}

		bool Init(cl_context context, cl_command_queue queue, cl_mem_flags flags, int size)
		{
			Clear();
			cl_int error;
			m_buffer = clCreateBuffer(context, flags, size, nullptr, &error);
			if (error != CL_SUCCESS)
				return (out_error() << "Can't create buffer for write" << std::endl, false);			
			m_queue = queue;
			return true;
		}

		bool Clear()
		{
			if (m_buffer)
			{
				clReleaseMemObject(m_buffer);
				m_buffer = nullptr;
			}
			return true;
		}


		bool Write(const void* data, int size)
		{
			cl_int error = clEnqueueWriteBuffer(m_queue, m_buffer, CL_TRUE, 0, size, data, 0, nullptr, nullptr);
			if (error != CL_SUCCESS)
				return (out_error() << "Can't write data in the buffer" << std::endl, false);
			return true;
		}

		bool Read(void* data, int size)
		{
			cl_int error = clEnqueueReadBuffer(m_queue, m_buffer, CL_TRUE, 0, size, data, 0, nullptr, nullptr);
			if (error != CL_SUCCESS)
				return (out_error() << "Can't read data in the buffer" << std::endl, false);
			return true;
		}
	};
}

#endif	//	_H_PUNK_OPENCL_BUFFER