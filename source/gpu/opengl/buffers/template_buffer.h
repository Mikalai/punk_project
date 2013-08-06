#ifndef _H_PUNK_OPENGL_TEMPLATE_BUFFER
#define _H_PUNK_OPENGL_TEMPLATE_BUFFER

#include "../error/module.h"
#include "../gl/module.h"

namespace OpenGL
{
	class VideoMemory;

	template<GLenum BufferType>
	class Buffer
	{
	public:

		Buffer();		
		~Buffer();
		void Bind();
		void Unbind();
		bool CopyData(void* data, unsigned size);
		const void* Map() const;
		void* Map();
		void Unmap();			

	private:
		size_t m_size;
		GLuint m_id;

	private:
		/**
		*	Only video memory class can allocate and release data
		*/
		friend class VideoMemory;

		bool Create(size_t size);
		bool Destroy();
	};

	template<GLenum BufferType>
	Buffer<BufferType>::Buffer()
		: m_id(0)
		, m_size(0)
	{}

	template<GLenum BufferType>
	Buffer<BufferType>::~Buffer()
	{
		try
		{
			Destroy();
		}
		catch(...)
		{}
	}

	template<GLenum BufferType>
	Buffer<BufferTypr>::Bind()
	{
		
	}
}

#endif	//	_H_PUNK_OPENGL_TEMPLATE_BUFFER