#include "platform_impl.h"

namespace OpenCL
{
	Platform::Platform() : m_impl(new PlatformImpl) {}
	Platform::Platform(const Platform& value) : m_impl(new PlatformImpl(*m_impl)) {}

	Platform& Platform::operator = (const Platform& value)
	{
		Platform temp(value);
		std::swap(temp.m_impl, m_impl);
		return *this;
	}

	Platform::~Platform()
	{
		m_impl.reset(nullptr);
	}

	bool Platform::Init()
	{
		return m_impl->Init();
	}
}
