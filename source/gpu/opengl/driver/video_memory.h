#ifndef _H_PUNK_OPENGL_VIDEO_MEMORY
#define _H_PUNK_OPENGL_VIDEO_MEMORY

#include <memory>
#include <vector>
#include "../../../config.h"
#include "../../../system/smart_pointers/proxy.h"

namespace GPU
{
	namespace OpenGL
	{
		class PixelBufferObject;
		class VertexBufferObject;
		class IndexBufferObject;

		/**
		*	This class is responsible for video memory usage
		*	Only this class can allocate video memory for
		*	textures and buffers.
		*	This is a singletone class
		*/
		class PUNK_ENGINE VideoMemory
		{
		public:

			VideoMemory();

			void SetMaxMemoryUsage(size_t value);
			size_t GetMaxMemoryUsage() const;
			size_t GetMemoryUsage() const;
			size_t GetMaxAvailableMemory() const;

			static VideoMemory* Instance();
			static void Destroy();

			System::Proxy<PixelBufferObject> AllocatePixelBuffer(size_t size);
			System::Proxy<VertexBufferObject> AllocateVertexBuffer(size_t size);
			System::Proxy<IndexBufferObject> AllocateIndexBuffer(size_t size);

		private:

			bool VerifyMemory(size_t size);

			/**
			*	This will use async procedures to find all invalid objects and
			*	when list of old objects will be created in the main stream
			*	memory freeing should be performed
			*/
			void OptimizeMemoryUsage(size_t size);

			static std::auto_ptr<VideoMemory> m_instance;		

			size_t m_max_mem_usage;
			size_t m_mem_usage;
			size_t m_max_mem_available;

			std::vector<System::Proxy<PixelBufferObject>> m_pbo_list;
			std::vector<System::Proxy<VertexBufferObject>> m_vbo_list;
			std::vector<System::Proxy<IndexBufferObject>> m_ibo_list;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_VIDEO_MEMORY