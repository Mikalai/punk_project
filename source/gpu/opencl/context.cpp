#include "context_impl.h"
#include "device_impl.h"

namespace GPU
{
	namespace OpenCL
	{
		Context::Context() : m_impl(new ContextImpl) {}
		Context::Context(const Context& value) : m_impl(new ContextImpl(*value.m_impl)) {}

		Context& Context::operator = (const Context& value)
		{
			Context temp(value);
			std::swap(temp.m_impl, m_impl);
			return *this;
		}

		Context::~Context()
		{
			m_impl.reset(nullptr);
		}

		bool Context::Init(Device& device)
		{
			return m_impl->Init(device.m_impl->m_device);
		}
	}
}