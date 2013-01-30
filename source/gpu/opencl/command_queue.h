#ifndef _H_PUNK_OPENCL_COMMAND_QUEUE
#define _H_PUNK_OPENCL_COMMAND_QUEUE

#include "../../config.h"
#include <memory>

namespace GPU
{
	namespace OpenCL
	{
		class Context;
		class Device;

		class PUNK_ENGINE CommandQueue
		{
		public:
			CommandQueue();
			CommandQueue(const CommandQueue&);
			CommandQueue& operator = (const CommandQueue&);
			~CommandQueue();

			bool Init(Context& context, Device& device);

			struct CommandQueueImpl;
			std::unique_ptr<CommandQueueImpl> m_impl;
		};
	}
}

#endif	//	_H_PUNK_OPENCL_COMMAND_QUEUE