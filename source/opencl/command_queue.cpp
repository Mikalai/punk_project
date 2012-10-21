#include "command_queue_impl.h"
#include "context_impl.h"
#include "device_impl.h"

namespace OpenCL
{
	CommandQueue::CommandQueue() : m_impl(new CommandQueueImpl) {}
	CommandQueue::CommandQueue(const CommandQueue& value) : m_impl(new CommandQueueImpl(*value.m_impl)) {}

	CommandQueue& CommandQueue::operator = (const CommandQueue& value)
	{
		CommandQueue temp(value);
		std::swap(temp.m_impl, m_impl);
		return *this;
	}

	CommandQueue::~CommandQueue()
	{
		m_impl.reset(nullptr);
	}

	bool CommandQueue::Init(Context& context, Device& device)
	{
		return m_impl->Int(context.m_impl->m_context, device.m_impl->m_device);
	}
}