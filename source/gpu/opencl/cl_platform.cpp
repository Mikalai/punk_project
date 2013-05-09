#include <algorithm>

#ifdef USE_OPENCL
#include "cl_platform_impl.h"
#else
#include "cl_platform.h"
#include "../../system/errors/module.h"
#endif

namespace GPU
{
	namespace OpenCL
	{
		Platform::Platform()
		#ifdef USE_OPENCL
		: m_impl(new PlatformImpl)
		#else
		: m_impl(nullptr)
		#endif
		 {}

		Platform::Platform(const Platform& value)
		#ifdef USE_OPENCL
		: m_impl(new PlatformImpl(*m_impl))
		#else
		: m_impl(nullptr)
		#endif
        {
#ifndef USE_OPENCL
            (void)value;
#endif
        }

		Platform& Platform::operator = (const Platform& value)
		{
			Platform temp(value);
			std::swap(temp.m_impl, m_impl);
			return *this;
		}

		Platform::~Platform()
		{
		    #ifdef USE_OPENCL
		    delete m_impl;
		    m_impl = nullptr;
		    #endif
		}

		bool Platform::Init()
		{
		    #ifdef USE_OPENCL
			return m_impl->Init();
			#else
			throw System::PunkException(L"OpenCL is not available");
			#endif
		}
	}
}
