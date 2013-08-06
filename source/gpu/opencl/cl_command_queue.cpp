#ifdef USE_OPENCL
#include "cl_command_queue_impl.h"
#include "cl_context_impl.h"
#include "cl_device_impl.h"
#else
#include "cl_command_queue.h"
#include "../../system/errors/module.h"
#endif

namespace Gpu
{
	namespace OpenCL
	{
		CommandQueue::CommandQueue()
		#ifdef USE_OPENCL
		: m_impl(new CommandQueueImpl)
		#else
		: m_impl(nullptr)
		#endif
		{}

		CommandQueue::CommandQueue(const CommandQueue& value)
		#ifdef USE_OPENCL
		: m_impl(new CommandQueueImpl(*value.m_impl))
		#else
		: m_impl(nullptr)
		#endif
        {
#ifndef USE_OPENCL
            (void)value;
#endif
        }

		CommandQueue& CommandQueue::operator = (const CommandQueue& value)
		{
			CommandQueue temp(value);
			std::swap(temp.m_impl, m_impl);
			return *this;
		}

		CommandQueue::~CommandQueue()
		{
		    #ifdef USE_OPENCL
			delete m_impl;
			m_impl = nullptr;
			#endif
		}

		bool CommandQueue::Init(Context& context, Device& device)
		{
		    #ifdef USE_OPENCL
			return m_impl->Int(context.m_impl->m_context, device.m_impl->m_device);
			#else
            (void)context; (void)device;
			throw System::PunkException(L"OpenCL is not available");
			#endif
		}
	}
}
