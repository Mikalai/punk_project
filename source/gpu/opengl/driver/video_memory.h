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
		class VideoMemory
		{
		public:

			VideoMemory();

			void SetMaxMemoryUsage(size_t value);
			size_t GetMaxMemoryUsage() const;
			size_t GetMemoryUsage() const;
			size_t GetMaxAvailableMemory() const;

        //	static VideoMemory* Instance();
        //	static void Destroy();

			PixelBufferObject* AllocatePixelBuffer(size_t size);
			void FreePixelBuffer(PixelBufferObject* value);
			VertexBufferObject* AllocateVertexBuffer(size_t size);
			void FreeVertexBuffer(VertexBufferObject* value);
			IndexBufferObject* AllocateIndexBuffer(size_t size);
			void FreeIndexBuffer(IndexBufferObject* value);

		private:

			bool VerifyMemory(size_t size);

			/**
			*	This will use async procedures to find all invalid objects and
			*	when list of old objects will be created in the main stream
			*	memory freeing should be performed
			*/
			void OptimizeMemoryUsage(size_t size);

        //	static std::unique_ptr<VideoMemory> m_instance;

			struct Core
			{
				size_t m_max_mem_usage;
				size_t m_mem_usage;
				size_t m_max_mem_available;
			};

			Core m_core;

			std::vector<PixelBufferObject*> m_pbo_list;
			std::vector<VertexBufferObject*> m_vbo_list;
			std::vector<IndexBufferObject*> m_ibo_list;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_VIDEO_MEMORY
