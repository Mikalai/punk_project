#include <algorithm>

#ifdef USE_OPENCL
#include "cl_program_impl.h"
#include "cl_context_impl.h"
#include "cl_device_impl.h"
#include "cl_command_queue_impl.h"
#else
#include "cl_program.h"
#include "../../system/errors/module.h"
#endif

namespace Gpu
{
	namespace OpenCL
	{
		Program::Program()
		#ifdef USE_OPENCL
		 : m_impl(new Program::ProgramImpl)
        #else
         : m_impl(nullptr)
        #endif
		 {}

		Program::Program(const Program& value)
		#ifdef USE_OPENCL
		: m_impl(new Program::ProgramImpl(*value.m_impl))
		#else
		: m_impl(nullptr)
		#endif
        {
#ifndef USE_OPENCL
            (void)value;
#endif
        }

		Program& Program::operator = (const Program& value)
		{
			Program temp(value);
			std::swap(temp.m_impl, m_impl);
			return *this;
		}

		bool Program::Init(Context& context, Device& device, CommandQueue& queue)
		{
		    #ifdef USE_OPENCL
			return m_impl->Init(context.m_impl->m_context, device.m_impl->m_device, queue.m_impl->m_queue);
			#else
            (void)context; (void)device; (void)queue;
			throw System::PunkException(L"OpenCL is not available");
			#endif
		}

		bool Program::CreateFromFile(const System::string& path)
		{
		    #ifdef USE_OPENCL
			return m_impl->CreateFromFile(path);
			#else
            (void)path;
			throw System::PunkException(L"OpenCL is not available");
			#endif
		}

		bool Program::GetKernel(const System::string& name, Kernel& value)
		{
		    #ifdef USE_OPENCL
			return m_impl->GetKernel(name, value);
			#else
            (void)name; (void)value;
			throw System::PunkException(L"OpenCL is not available");
			#endif
		}

		Program::~Program()
		{
		    #ifdef USE_OPENCL
			delete m_impl;
			m_impl = nullptr;
			#endif
		}
	}
}
