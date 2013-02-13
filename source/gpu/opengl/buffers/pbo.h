#ifndef _H_PUNK_OPENGL_PIXEL_BUFFER_OBJECT
#define _H_PUNK_OPENGL_PIXEL_BUFFER_OBJECT

#include "../gl/module.h"

namespace GPU
{
	namespace OpenGL
	{
		class VideoMemory;

		class PUNK_ENGINE PixelBufferObject
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
			PixelBufferObject();
			~PixelBufferObject();

			PixelBufferObject(const PixelBufferObject&);
			PixelBufferObject& operator = (const PixelBufferObject&);
			
			GLuint m_index;
			size_t m_size;

			friend class VideoMemory;
		};
	}
}

#endif	//	_H_PUNK_OPENGL_PIXEL_BUFFER_OBJECT
