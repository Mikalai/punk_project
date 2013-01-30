#include "video_memory.h"
#include "../gl/module.h"
#include "../buffers/module.h"

namespace GPU
{
	namespace OpenGL
	{
		std::auto_ptr<VideoMemory> VideoMemory::m_instance;		
		VideoMemory* VideoMemory::Instance()
		{
			if (!m_instance.get())
				m_instance.reset(new VideoMemory);
			return m_instance.get();
		}

		void VideoMemory::Destroy()
		{
			m_instance.reset(0);
		}

		VideoMemory::VideoMemory()
		{
			GLint mem[5] = {0, 0, 0, 0};
			glGetIntegerv(GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &mem[0]);
			m_max_mem_available = mem[0];
			glGetIntegerv(GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &mem[1]);
			glGetIntegerv(GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &mem[2]);
			glGetIntegerv(GPU_MEMORY_INFO_EVICTION_COUNT_NVX, &mem[3]);
			glGetIntegerv(GPU_MEMORY_INFO_EVICTED_MEMORY_NVX, &mem[4]);
			m_max_mem_usage = (m_max_mem_available << 1) / 3;			
		}

		void VideoMemory::SetMaxMemoryUsage(size_t value)
		{
		}

		size_t VideoMemory::GetMaxMemoryUsage() const
		{
			return m_max_mem_usage;
		}

		size_t VideoMemory::GetMemoryUsage() const
		{
			return m_mem_usage;
		}

		size_t VideoMemory::GetMaxAvailableMemory() const
		{
			return m_max_mem_available;
		}

		System::Proxy<PixelBufferObject> VideoMemory::AllocatePixelBuffer(size_t size)
		{
			System::Proxy<PixelBufferObject> value;
			if (VerifyMemory(size))
			{
				value.Reset(new PixelBufferObject);
				m_pbo_list.push_back(value);
			}
			return value;
		}

		System::Proxy<VertexBufferObject> VideoMemory::AllocateVertexBuffer(size_t size)
		{
			System::Proxy<VertexBufferObject> value;
			if (VerifyMemory(size))
			{
				value.Reset(new VertexBufferObject);
				m_vbo_list.push_back(value);
			}
			return value;
		}

		System::Proxy<IndexBufferObject> VideoMemory::AllocateIndexBuffer(size_t size)
		{
			System::Proxy<IndexBufferObject> value;
			if (VerifyMemory(size))
			{
				value.Reset(new IndexBufferObject);
				m_ibo_list.push_back(value);
			}
			return value;
		}

		bool VideoMemory::VerifyMemory(size_t size)
		{
			if (m_mem_usage + size >= m_max_mem_usage)
			{
				OptimizeMemoryUsage(size);
				if (m_mem_usage + size >= m_max_mem_usage)
					return false;
			}
			return true;
		}

		void VideoMemory::OptimizeMemoryUsage(size_t size)
		{		
			size_t to_free = 0;
			//	remove useless textures
			for (size_t i = 0; i < m_pbo_list.size(); ++i)
			{
				if (m_pbo_list[i].GetCount() == 1)
					to_free += m_pbo_list[i]->GetSize();
				if (m_mem_usage - to_free + size < m_max_mem_usage)
					return;
			}

			//	remove useless vbo
			for (size_t i = 0; i < m_vbo_list.size(); ++i)
			{
				if (m_vbo_list[i].GetCount() == 1)
					to_free += m_vbo_list[i]->GetSize();
				if (m_mem_usage - to_free + size < m_max_mem_usage)
					return;
			}

			//	remove useless ibo
			for (size_t i = 0; i < m_ibo_list.size(); ++i)
			{
				if (m_ibo_list[i].GetCount() == 1)
					to_free += m_ibo_list[i]->GetSize();
				if (m_mem_usage - to_free + size < m_max_mem_usage)
					return;
			}
		}

	}
}