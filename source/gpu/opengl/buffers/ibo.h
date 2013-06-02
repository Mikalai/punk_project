#ifndef _H_PUNK_OPENGL_INDEX_BUFFER
#define _H_PUNK_OPENGL_INDEX_BUFFER

#include "../gl/module.h"

namespace GPU
{
	namespace OpenGL
	{
		class VideoMemory;

        class PUNK_ENGINE_LOCAL IndexBufferObject
		{
		public:
			
            void PUNK_ENGINE_LOCAL Create(const void* data, size_t m_size);
            void PUNK_ENGINE_LOCAL Destroy();

            void PUNK_ENGINE_LOCAL Bind() const;
            void PUNK_ENGINE_LOCAL Unbind() const;

            void* PUNK_ENGINE_LOCAL Map();
            const void* PUNK_ENGINE_LOCAL Map() const;
            void PUNK_ENGINE_LOCAL Unmap() const;

            void PUNK_ENGINE_LOCAL CopyData(const void* data, size_t size);

            bool PUNK_ENGINE_LOCAL IsValid() const;

            size_t PUNK_ENGINE_LOCAL GetSize() const { return m_size; }

		private:		

			//	Only VideoMemory can create it
            PUNK_ENGINE_LOCAL IndexBufferObject();
            PUNK_ENGINE_LOCAL ~IndexBufferObject();

            PUNK_ENGINE_LOCAL IndexBufferObject(const IndexBufferObject&);
            PUNK_ENGINE_LOCAL IndexBufferObject& operator = (const IndexBufferObject&);
			
            PUNK_ENGINE_LOCAL GLuint m_index;
            PUNK_ENGINE_LOCAL size_t m_size;

			friend class VideoMemory;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_INDEX_BUFFER
