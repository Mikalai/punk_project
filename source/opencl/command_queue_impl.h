#ifndef _H_PUNK_OPENCL_COMMAND_QUEUE_IMPL
#define _H_PUNK_OPENCL_COMMAND_QUEUE_IMPL

#include <CL/opencl.h>
#include "command_queue.h"
#include "../system/logger.h"

namespace OpenCL
{
	struct CommandQueue::CommandQueueImpl
	{
		cl_command_queue m_queue;
		
		CommandQueueImpl() : m_queue(0) {}

		bool Int(cl_context context, cl_device_id device)
		{
			Clear();
			cl_int error;
			m_queue = clCreateCommandQueue(context, device, 0, &error);
			if (error != CL_SUCCESS)
				return (out_error() << "Can't create OpenCL command queue" << std::endl, false);
			return true;
		}

		bool Clear()
		{
			if (m_queue)
			{
				cl_int error = clReleaseCommandQueue(m_queue);
				if (error != CL_SUCCESS)
					return (out_error() << "Can't release command queue" << std::endl, false);
			}
			return true;
		}

		~CommandQueueImpl()
		{
			Clear();
		}
	};
}

#endif	//	_H_PUNK_OPENCL_COMMAND_QUEUE_IMPL