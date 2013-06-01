#include "vbo.h"

namespace GPU
{
	namespace OpenGL
	{
		VertexBufferObject::VertexBufferObject() 
			: m_index(0)
			, m_size(0)
		{}

		VertexBufferObject::~VertexBufferObject()
		{
			try
			{
				Destroy();
			}
			catch(...)
			{}
		}

		void VertexBufferObject::Create(const void* data, size_t size)
		{
			if (IsValid())
				Destroy();

			glGenBuffers(1, &m_index);
			ValidateOpenGL(L"Unable to generate vertex buffer");
			glBindBuffer(GL_ARRAY_BUFFER, m_index);
			ValidateOpenGL(L"Unable to bind vertex buffer");
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			ValidateOpenGL(L"Unable to fill vertex buffer with data");
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			ValidateOpenGL(L"Unable to unbind vertex buffer");	
			m_size = size;
		}

		void VertexBufferObject::Destroy()
		{
			if (m_index)
			{
				glDeleteBuffers(1, &m_index);				
				ValidateOpenGL(L"Unable to delete vertext buffer");
				m_index = 0;
			}
		}

		bool VertexBufferObject::IsValid() const
		{
			return m_index != 0;
		}

		void VertexBufferObject::Bind() const
		{
			if (!IsValid())
				throw OpenGLInvalidValueException(L"Buffer is not valid");

			glBindBuffer(GL_ARRAY_BUFFER, m_index);
			ValidateOpenGL(L"Unable to bind vertex buffer");
		}

		void VertexBufferObject::Unbind() const
		{
			if (!IsValid())
				throw OpenGLInvalidValueException(L"Buffer is not valid");
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			ValidateOpenGL(L"Unable to unbind vertex buffer");
		}


		void* VertexBufferObject::Map()
		{
			Bind();
			GLvoid* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
			ValidateOpenGL(L"Unable to map buffer");
			Unbind();
			return buffer;
		}

		const void* VertexBufferObject::Map() const
		{
			Bind();
			GLvoid* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_BUFFER);
			ValidateOpenGL(L"Unable to map buffer");
			Unbind();
			return buffer;			
		}

		void VertexBufferObject::Unmap() const
		{
			Bind();
			glUnmapBuffer(GL_ARRAY_BUFFER);
			ValidateOpenGL(L"Unable to map buffer");
			Unbind();
		}

		void VertexBufferObject::CopyData(const void* data, size_t size)
		{
			if (m_size < size)
				throw OpenGLOutOfMemoryException(L"Vertex buffer is to small " + System::string::Convert(m_size) + L" to hold " + System::string::Convert(size));
			Bind();
			glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
			Unbind();
		}
	}
}