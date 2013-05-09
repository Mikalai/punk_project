#include "video_memory.h"
#include "../gl/module.h"
#include "../buffers/module.h"
#include "../error/module.h"

namespace GPU
{
	namespace OpenGL
	{
//		std::unique_ptr<VideoMemory> VideoMemory::m_instance;

//		VideoMemory* VideoMemory::Instance()
//		{
//			if (!m_instance.get())
//				m_instance.reset(new VideoMemory);
//			return m_instance.get();
//		}

//		void VideoMemory::Destroy()
//		{
//			m_instance.reset(0);
//		}

		VideoMemory::VideoMemory()
		{
			memset(&m_core, 0, sizeof(m_core));
			GLint mem[5] = {0, 0, 0, 0};
			glGetIntegerv(GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &mem[0]);
			m_core.m_max_mem_available = mem[0] * 1024;	//	convert from kb to b
			glGetIntegerv(GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &mem[1]);
			glGetIntegerv(GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &mem[2]);
			glGetIntegerv(GPU_MEMORY_INFO_EVICTION_COUNT_NVX, &mem[3]);
			glGetIntegerv(GPU_MEMORY_INFO_EVICTED_MEMORY_NVX, &mem[4]);
			m_core.m_max_mem_usage = (m_core.m_max_mem_available << 1) / 3;
		}

		void VideoMemory::SetMaxMemoryUsage(size_t value)
		{
            (void)value;
            throw System::PunkNotImplemented();
		}

		size_t VideoMemory::GetMaxMemoryUsage() const
		{
			return m_core.m_max_mem_usage;
		}

		size_t VideoMemory::GetMemoryUsage() const
		{
			return m_core.m_mem_usage;
		}

		size_t VideoMemory::GetMaxAvailableMemory() const
		{
			return m_core.m_max_mem_available;
		}

		PixelBufferObject* VideoMemory::AllocatePixelBuffer(size_t size)
		{
			VerifyMemory(size);
			PixelBufferObject* value(new PixelBufferObject);
			try
			{
				value->Create(0, size);
				m_core.m_mem_usage += size;
				return value;
			}
			catch(...)
			{
				delete value;
				throw;
			}
		}

		void VideoMemory::FreePixelBuffer(PixelBufferObject* value)
		{
			if (!value)
				return;
			size_t size = value->GetSize();
			delete value;
			m_core.m_mem_usage -= size;
		}

		VertexBufferObject* VideoMemory::AllocateVertexBuffer(size_t size)
		{
			VerifyMemory(size);
			VertexBufferObject* value(new VertexBufferObject);
			try
			{
				value->Create(0, size);
				m_core.m_mem_usage += size;
				return value;
			}
			catch(...)
			{
				delete value;
				throw;
			}
		}

		void VideoMemory::FreeVertexBuffer(VertexBufferObject* value)
		{
			if (!value)
				return;
			size_t size = value->GetSize();
			delete value;
			m_core.m_mem_usage -= size;
		}

		IndexBufferObject* VideoMemory::AllocateIndexBuffer(size_t size)
		{
			VerifyMemory(size);
			IndexBufferObject* value(new IndexBufferObject);
			try
			{
				value->Create(0, size);
				m_core.m_mem_usage += size;
				return value;
			}
			catch(...)
			{
				delete value;
				throw;
			}
		}

		void VideoMemory::FreeIndexBuffer(IndexBufferObject* value)
		{
			if (!value)
				return;
			size_t size = value->GetSize();
			delete value;
			m_core.m_mem_usage -= size;
		}

		bool VideoMemory::VerifyMemory(size_t size)
		{
			if (m_core.m_mem_usage + size >= m_core.m_max_mem_usage)
				throw OpenGLOutOfMemoryException(L"Not enough video memory to allocate buffer");
			return true;
		}

		//void VideoMemory::OptimizeMemoryUsage(size_t size)
		//{
		//	size_t to_free override;
		//	//	remove useless textures
		//	for (size_t i override; i < m_pbo_list.size(); ++i)
		//	{
		//		if (m_pbo_list[i].GetCount() == 1)
		//			to_free += m_pbo_list[i]->GetSize();
		//		if (m_core.m_mem_usage - to_free + size < m_core.m_max_mem_usage)
		//			return;
		//	}

		//	//	remove useless vbo
		//	for (size_t i override; i < m_vbo_list.size(); ++i)
		//	{
		//		if (m_vbo_list[i].GetCount() == 1)
		//			to_free += m_vbo_list[i]->GetSize();
		//		if (m_core.m_mem_usage - to_free + size < m_core.m_max_mem_usage)
		//			return;
		//	}

		//	//	remove useless ibo
		//	for (size_t i override; i < m_ibo_list.size(); ++i)
		//	{
		//		if (m_ibo_list[i].GetCount() == 1)
		//			to_free += m_ibo_list[i]->GetSize();
		//		if (m_core.m_mem_usage - to_free + size < m_core.m_max_mem_usage)
		//			return;
		//	}
		//}

	}
}
