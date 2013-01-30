#include "kernel_impl.h"

namespace GPU
{
	namespace OpenCL
	{
		Kernel::Kernel() : m_impl(new Kernel::KernelImpl) {}
		Kernel::Kernel(const Kernel& value) : m_impl(new Kernel::KernelImpl(*value.m_impl)) {}

		Kernel& Kernel::operator = (const Kernel& value)
		{
			Kernel temp(value);
			std::swap(temp.m_impl, m_impl);
			return *this;
		}

		Kernel::~Kernel()
		{
			m_impl.reset(nullptr);
		}

		bool Kernel::Call(int value)
		{
			return m_impl->Call(value);
		}

		bool Kernel::SetArgument(int index, Buffer& value)
		{
			return m_impl->SetArgument(index, value);
		}

		bool Kernel::SetArgument(int index, int value)
		{
			return m_impl->SetArgument(index, value);
		}

	}
}