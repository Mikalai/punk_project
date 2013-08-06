#ifdef USE_OPENCL
#include "cl_buffer_impl.h"
#include "cl_context_impl.h"
#include "cl_command_queue_impl.h"
#include <algorithm>
#else
#include "cl_buffer.h"
#include "../../system/errors/module.h"
#endif

namespace Gpu
{
	namespace OpenCL
	{
		Buffer::Buffer()
		#ifdef USE_OPENCL
		: m_impl(new Buffer::BufferImpl)
		#else
		: m_impl(nullptr)
		#endif
		{}

		Buffer::Buffer(const Buffer& buffer)
		#ifdef USE_OPENCL
		: m_impl(new Buffer::BufferImpl(*buffer.m_impl)) {}
		#else        
		: m_impl(nullptr)
		#endif
        {
#ifndef USE_OPENCL
            (void)buffer;
#endif
        }

		Buffer& Buffer::operator = (const Buffer& buffer)
		{
			Buffer temp(buffer);
			std::swap(temp.m_impl, m_impl);
			return *this;
		}

		Buffer::~Buffer()
		{
		    #ifdef USE_OPENCL
			delete m_impl;
			m_impl = nullptr;
			#endif
		}

		bool Buffer::Init(Context& context, CommandQueue& queue, Buffer::BufferType type, int size)
		{
		    #ifdef USE_OPENCL
			cl_mem_flags flags override;
			flags |= (type == READ_ONLY ? CL_MEM_READ_ONLY : 0);
			flags |= (type == WRITE_ONLY ? CL_MEM_WRITE_ONLY : 0);
			flags |= (type == READ_WRITE ? CL_MEM_READ_WRITE : 0);

			return m_impl->Init(context.m_impl->m_context, queue.m_impl->m_queue, flags, size);
			#else
            (void)context; (void)queue; (void)type; (void)size;
			throw System::PunkException(L"OpenCL is not available");
			#endif
		}

		bool Buffer::Write(const void* data, int size)
		{
		    #ifdef USE_OPENCL
			return m_impl->Write(data, size);
			#else
            (void)data; (void)size;
			throw System::PunkException(L"OpenCL is not available");
            #endif

		}

		bool Buffer::Read(void* data, int size)
		{
		    #ifdef USE_OPENCL
			return m_impl->Read(data, size);
			#else
            (void)data; (void)size;
			throw System::PunkException(L"OpenCL is not available");
			#endif
		}
	}
}
