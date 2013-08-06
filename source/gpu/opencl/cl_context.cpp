#ifdef USE_OPENCL
#include "cl_context_impl.h"
#include "cl_device_impl.h"
#else
#include "cl_context.h"
#include "../../system/errors/module.h"
#endif

namespace Gpu
{
	namespace OpenCL
	{
		Context::Context()
		#ifdef USE_OPENCL
		: m_impl(new ContextImpl)
		#else
		: m_impl(nullptr)
		#endif
		{}

		Context::Context(const Context& value)
		#ifdef USE_OPENCL
		: m_impl(new ContextImpl(*value.m_impl))
		#else
		: m_impl(nullptr)
		#endif
        {
#ifndef USE_OPENCL
            (void)value;
#endif
        }

		Context& Context::operator = (const Context& value)
		{
			Context temp(value);
			std::swap(temp.m_impl, m_impl);
			return *this;
		}

		Context::~Context()
		{
		    #ifdef USE_OPENCL
            delete m_impl;
            m_impl = nullptr;
            #endif
		}

		bool Context::Init(Device& device)
		{
		    #ifdef USE_OPENCL
			return m_impl->Init(device.m_impl->m_device);
			#else
            (void)device;
			throw System::PunkException(L"OpenCL is not available");
			#endif
		}
	}
}
