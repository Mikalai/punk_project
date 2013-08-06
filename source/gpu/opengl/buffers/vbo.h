#ifndef _H_PUNK_OPENGL_BUFFER
#define _H_PUNK_OPENGL_BUFFER

#include "../gl/module.h"

namespace Gpu
{
	namespace OpenGL
	{
		class VideoMemory;

        class PUNK_ENGINE_LOCAL VertexBufferObject
		{
		public:
			
			void Create(const void* data, size_t m_size);
			void Destroy();			

			void Bind() const;
			void Unbind() const;

			void* Map();
			const void* Map() const;
			void Unmap() const;

			void CopyData(const void* data, size_t size);

			bool IsValid() const;

			size_t GetSize() const { return m_size; }

		private:		

			//	Only VideoMemory can create it
			VertexBufferObject();
			~VertexBufferObject();

			VertexBufferObject(const VertexBufferObject&);
			VertexBufferObject& operator = (const VertexBufferObject&);
			
			GLuint m_index;
			size_t m_size;

			friend class VideoMemory;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_BUFFER
