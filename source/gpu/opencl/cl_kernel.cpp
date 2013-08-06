#ifdef USE_OPENCL
#include "cl_kernel_impl.h"
#else
#include "cl_kernel.h"
#include "../../system/errors/module.h"
#endif

namespace Gpu
{
	namespace OpenCL
	{
		Kernel::Kernel()
		#ifdef USE_OPENCL
		: m_impl(new Kernel::KernelImpl)
		#else
		: m_impl(nullptr)
		#endif
		{}

		Kernel::Kernel(const Kernel& value)
		#ifdef USE_OPENCL
		: m_impl(new Kernel::KernelImpl(*value.m_impl))
		#else
		: m_impl(nullptr)
		#endif
        {
#ifndef USE_OPENCL
            (void)value;
#endif
        }

		Kernel& Kernel::operator = (const Kernel& value)
		{
			Kernel temp(value);
			std::swap(temp.m_impl, m_impl);
			return *this;
		}

		Kernel::~Kernel()
		{
		    #ifdef USE_OPENCL
			delete m_impl;
			m_impl = nullptr;
			#endif
		}

		bool Kernel::Call(int value)
		{
		    #ifdef USE_OPENCL
			return m_impl->Call(value);
			#else
            (void)value;
			throw System::PunkException(L"OpenCL is not available");
			#endif
		}

		bool Kernel::SetArgument(int index, Buffer& value)
		{
		    #ifdef USE_OPENCL
			return m_impl->SetArgument(index, value);
			#else
            (void)value; (void)index;
			throw System::PunkException(L"OpenCL is not available");
			#endif
		}

		bool Kernel::SetArgument(int index, int value)
		{
		    #ifdef USE_OPENCL
			return m_impl->SetArgument(index, value);
			#else
            (void)index; (void)value;
			throw System::PunkException(L"OpenCL is not available");
			#endif
		}

	}
}
