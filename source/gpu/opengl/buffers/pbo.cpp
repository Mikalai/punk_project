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

			glGenBuffers(1, &m_index);
			CHECK_GL_ERROR(L"Unable to generate pixel buffer");
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_index);
			CHECK_GL_ERROR(L"Unable to bind pixel buffer");
			glBufferData(GL_PIXEL_UNPACK_BUFFER, size, data, GL_STATIC_DRAW);
			CHECK_GL_ERROR(L"Unable to fill pixel buffer with data");
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
			CHECK_GL_ERROR(L"Unable to unbind pixel buffer");	
			m_size = size;
		}

		void PixelBufferObject::Destroy()
		{
			if (m_index)
			{
				glDeleteBuffers(1, &m_index);				
				CHECK_GL_ERROR(L"Unable to delete pixel buffer");
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

			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_index);
			CHECK_GL_ERROR(L"Unable to bind pixel buffer");
		}

		void PixelBufferObject::Unbind() const
		{
			if (!IsValid())
				throw OpenGLInvalidValueException(L"Buffer is not valid");
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
			CHECK_GL_ERROR(L"Unable to unbind pixel buffer");
		}


		void* PixelBufferObject::Map()
		{
			Bind();
			glBufferData(GL_PIXEL_UNPACK_BUFFER, m_size, 0, GL_STREAM_DRAW);
			CHECK_GL_ERROR(L"Unable drop buffer");
			GLvoid* buffer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_READ_WRITE);
			CHECK_GL_ERROR(L"Unable to map buffer");
			Unbind();
			return buffer;
		}

		const void* PixelBufferObject::Map() const
		{
			Bind();
			GLvoid* buffer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_READ_BUFFER);
			CHECK_GL_ERROR(L"Unable to map buffer");
			Unbind();
			return buffer;			
		}

		void PixelBufferObject::Unmap() const
		{
			Bind();
			glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
			CHECK_GL_ERROR(L"Unable to map buffer");
			Unbind();
		}

		void PixelBufferObject::CopyData(const void* data, size_t size)
		{
			if (m_size < size)
				throw OpenGLOutOfMemoryException(L"pixel buffer is to small " + System::string::Convert(m_size) + L" to hold " + System::string::Convert(size));
			Bind();
			glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, size, data);
			Unbind();
		}
	}
}