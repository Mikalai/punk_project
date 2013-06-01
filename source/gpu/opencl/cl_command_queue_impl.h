#ifndef _H_PUNK_OPENCL_COMMAND_QUEUE_IMPL
#define _H_PUNK_OPENCL_COMMAND_QUEUE_IMPL

#ifdef USE_OPENCL
#include <CL/opencl.h>
#include "errors/module.h"
#include "cl_command_queue.h"
#endif

namespace GPU
{
	namespace OpenCL
	{
	    #ifdef USE_OPENCL
		struct CommandQueue::CommandQueueImpl
		{
			cl_command_queue m_queue;

			CommandQueueImpl() : m_queue(0) {}

			bool Int(cl_context context, cl_device_id device)
			{
				Clear();
				cl_int error;
				m_queue = clCreateCommandQueue(context, device, 0, &error);
				CHECK_CL_ERROR(error, L"Can't create OpenCL command queue");
				return true;
			}

			bool Clear()
			{
				if (m_queue)
				{
					cl_int error = clReleaseCommandQueue(m_queue);
					CHECK_CL_ERROR(error, L"Can't release command queue");
				}
				return true;
			}

			~CommandQueueImpl()
			{
				Clear();
			}
		};
		#endif
	}
}

#endif	//	_H_PUNK_OPENCL_COMMAND_QUEUE_IMPL
