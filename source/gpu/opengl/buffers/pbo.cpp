#include "pbo.h"

namespace GPU
{
	namespace OpenGL
	{
		PixelBufferObject::PixelBufferObject() 
			: m_index(0)
			, m_size(0)
		{}

		PixelBufferObject::~PixelBufferObject()
		{
			try
			{
				Destroy();
			}
			catch(...)
			{}
		}

		void PixelBufferObject::Create(const void* data, size_t size)
		{
			if (IsValid())
				Destroy();

            GL_CALL(glGenBuffers(1, &m_index));
            GL_CALL(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_index));
            GL_CALL(glBufferData(GL_PIXEL_UNPACK_BUFFER, size, data, GL_STATIC_DRAW));
            GL_CALL(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));
			m_size = size;
		}

		void PixelBufferObject::Destroy()
		{
			if (m_index)
			{
                GL_CALL(glDeleteBuffers(1, &m_index));
				m_index = 0;
			}
		}

		bool PixelBufferObject::IsValid() const
		{
			return m_index != 0;
		}

		void PixelBufferObject::Bind() const
		{
			if (!IsValid())
				throw OpenGLInvalidValueException(L"Buffer is not valid");

            GL_CALL(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_index));
		}

		void PixelBufferObject::Unbind() const
		{
			if (!IsValid())
				throw OpenGLInvalidValueException(L"Buffer is not valid");
            GL_CALL(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));
		}


		void* PixelBufferObject::Map()
		{
			Bind();
            GL_CALL(glBufferData(GL_PIXEL_UNPACK_BUFFER, m_size, 0, GL_STREAM_DRAW));
            GL_CALL(GLvoid* buffer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_READ_WRITE));
			Unbind();
			return buffer;
		}

		const void* PixelBufferObject::Map() const
		{
			Bind();
            GL_CALL(GLvoid* buffer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_READ_WRITE));
			Unbind();
			return buffer;			
		}

		void PixelBufferObject::Unmap() const
		{
			Bind();
            GL_CALL(glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER));
			Unbind();
		}

		void PixelBufferObject::CopyData(const void* data, size_t size)
		{
			if (m_size < size)
				throw OpenGLOutOfMemoryException(L"pixel buffer is to small " + System::string::Convert(m_size) + L" to hold " + System::string::Convert(size));
			Bind();
            GL_CALL(glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, size, data));
			Unbind();
		}
	}
}
