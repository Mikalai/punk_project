#ifndef _H_PUNK_OPENCL_COMMAND_QUEUE
#define _H_PUNK_OPENCL_COMMAND_QUEUE

#include "../../config.h"

namespace GPU
{
	namespace OpenCL
	{
		class Context;
		class Device;

		class PUNK_ENGINE_API CommandQueue
		{
		public:
			CommandQueue();
			CommandQueue(const CommandQueue&);
			CommandQueue& operator = (const CommandQueue&);
			~CommandQueue();

			bool Init(Context& context, Device& device);

			struct CommandQueueImpl;
			CommandQueueImpl* m_impl;
		};
	}
}

#endif	//	_H_PUNK_OPENCL_COMMAND_QUEUE
