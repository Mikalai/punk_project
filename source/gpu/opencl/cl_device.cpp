#ifdef USE_OPENCL
#include "cl_device_impl.h"
#include "cl_platform_impl.h"
#else
#include "cl_device.h"
#include "../../system/errors/module.h"
#endif

namespace GPU
{
	namespace OpenCL
	{
		Device::Device()
		#ifdef USE_OPENCL
		: m_impl(new Device::DeviceImpl)
		#else
		: m_impl(nullptr)
		#endif
		{}

		Device::Device(const Device& value)
		#ifdef USE_OPENCL
		: m_impl(new Device::DeviceImpl(*value.m_impl))
		#else
		: m_impl(nullptr)
		#endif
        {
#ifndef USE_OPENCL
            (void)value;
#endif
        }

		Device& Device::operator = (const Device& value)
		{
			Device temp(value);
			std::swap(temp.m_impl, m_impl);
			return *this;
		}

		Device::~Device()
		{
		    #ifdef USE_OPENCL
		    delete m_impl;
		    m_impl = nullptr;
		    #endif
		}


		bool Device::Init(Platform& platform)
		{
		    #ifdef USE_OPENCL
			return m_impl->Init(platform.m_impl->m_platform);
			#else
            (void)platform;
			throw System::PunkException(L"OpenCL is not available");
			#endif
		}
	}
}
