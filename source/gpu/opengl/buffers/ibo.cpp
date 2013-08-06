#include "ibo.h"

namespace Gpu
{
	namespace OpenGL
	{
		IndexBufferObject::IndexBufferObject() 
			: m_index(0)
			, m_size(0)
		{}

		IndexBufferObject::~IndexBufferObject()
		{
			try
			{
				Destroy();
			}
			catch(...)
			{}
		}

		void IndexBufferObject::Create(const void* data, size_t size)
		{
			if (IsValid())
				Destroy();

            GL_CALL(glGenBuffers(1, &m_index));
            GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index));
            GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
            GL_CALL(ValidateOpenGL(L"Unable to fill Index buffer with data"));
            GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
            GL_CALL(ValidateOpenGL(L"Unable to unbind Index buffer"));
			m_size = size;
		}

		void IndexBufferObject::Destroy()
		{
			if (m_index)
			{
				glDeleteBuffers(1, &m_index);				
				ValidateOpenGL(L"Unable to delete Indext buffer");
                m_index = 0;
			}
		}

		bool IndexBufferObject::IsValid() const
		{
			return m_index != 0;
		}

		void IndexBufferObject::Bind() const
		{
			if (!IsValid())
				throw OpenGLInvalidValueException(L"Buffer is not valid");

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
			ValidateOpenGL(L"Unable to bind Index buffer");
		}

		void IndexBufferObject::Unbind() const
		{
			if (!IsValid())
				throw OpenGLInvalidValueException(L"Buffer is not valid");
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			ValidateOpenGL(L"Unable to unbind Index buffer");
		}


		void* IndexBufferObject::Map()
		{
			Bind();
			GLvoid* buffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);
			ValidateOpenGL(L"Unable to map buffer");
			Unbind();
			return buffer;
		}

		const void* IndexBufferObject::Map() const
		{
			Bind();
			GLvoid* buffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_BUFFER);
			ValidateOpenGL(L"Unable to map buffer");
			Unbind();
			return buffer;			
		}

		void IndexBufferObject::Unmap() const
		{
			Bind();
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
			ValidateOpenGL(L"Unable to map buffer");
			Unbind();
		}

		void IndexBufferObject::CopyData(const void* data, size_t size)
		{
			if (m_size < size)
				throw OpenGLOutOfMemoryException(L"Index buffer is to small " + System::string::Convert(m_size) + L" to hold " + System::string::Convert(size));
			Bind();
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
			Unbind();
		}
	}
}
