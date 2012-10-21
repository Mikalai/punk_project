#include "device_impl.h"
#include "platform_impl.h"

namespace OpenCL
{
	Device::Device() : m_impl(new Device::DeviceImpl) {}
	Device::Device(const Device& value) : m_impl(new Device::DeviceImpl(*value.m_impl)) {}

	Device& Device::operator = (const Device& value)
	{
		Device temp(value);
		std::swap(temp.m_impl, m_impl);
		return *this;
	}

	Device::~Device()
	{
		m_impl.reset(nullptr);
	}


	bool Device::Init(Platform& platform)
	{
		return m_impl->Init(platform.m_impl->m_platform);
	}
}