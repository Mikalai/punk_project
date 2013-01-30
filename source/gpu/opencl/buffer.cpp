#include "buffer_impl.h"
#include "context_impl.h"
#include "command_queue_impl.h"
#include <algorithm>

namespace GPU
{
	namespace OpenCL
	{
		Buffer::Buffer() : m_impl(new Buffer::BufferImpl) {}
		Buffer::Buffer(const Buffer& buffer) : m_impl(new Buffer::BufferImpl(*buffer.m_impl)) {}

		Buffer& Buffer::operator = (const Buffer& buffer)
		{
			Buffer temp(buffer);
			std::swap(temp.m_impl, m_impl);
			return *this;
		}

		Buffer::~Buffer()
		{
			m_impl.reset(nullptr);
		}

		bool Buffer::Init(Context& context, CommandQueue& queue, Buffer::BufferType type, int size)
		{
			cl_mem_flags flags = 0;
			flags |= (type == READ_ONLY ? CL_MEM_READ_ONLY : 0);
			flags |= (type == WRITE_ONLY ? CL_MEM_WRITE_ONLY : 0);
			flags |= (type == READ_WRITE ? CL_MEM_READ_WRITE : 0);

			return m_impl->Init(context.m_impl->m_context, queue.m_impl->m_queue, flags, size);
		}

		bool Buffer::Write(const void* data, int size)
		{
			return m_impl->Write(data, size);
		}

		bool Buffer::Read(void* data, int size)
		{
			return m_impl->Read(data, size);
		}
	}
}