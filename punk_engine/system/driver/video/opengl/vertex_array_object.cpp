//
//	
//

#include "win32/driver_win32.h"
#include "vertex_array_object.h"
#include "shader_program.h"
#include "../../../../utility/model/vertex.h"

namespace OpenGL
{
	VertexArrayObject::~VertexArrayObject()
	{
		glDeleteBuffers(1, &m_index_buffer);
		glDeleteBuffers(1, &m_vertex_buffer);
		glDeleteVertexArrays(1, &m_vertex_array);
	}

	void VertexArrayObject::Bind() const
	{
		glBindVertexArray(m_vertex_array);
	}

	void VertexArrayObject::Unbind() const
	{
		glBindVertexArray(0);
	}

	int VertexArrayObject::GetIndexCount() const
	{
		return m_index_count;
	}

	void VertexArrayObject::Render()
	{

		glBindVertexArray(m_vertex_array);

		glDrawElementsInstanced(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0, 1);

		//glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0);			

		glBindVertexArray(0);
	}

	bool VertexArrayObject::CreateQuad()
	{
		Utility::VertexPositionTexture v[4];
		memset(v, 0, sizeof(v));
		v[0].x = -1; v[0].y = -1; v[0].u = 0; v[0].v = 0;
		v[1].x = -1; v[1].y =  1; v[0].u = 0; v[0].v = 1;
		v[2].x =  1; v[2].y =  1; v[0].u = 1; v[0].v = 1;
		v[3].x =  1; v[3].y = -1; v[0].u = 1; v[0].v = 0;

		int buffer_size = sizeof(v);
		unsigned index[] = {0, 1, 2, 2, 3, 0};
		m_index_count = 6;
		int code = Utility::COMPONENT_POSITION | Utility::COMPONENT_TEXTURE;

		GLenum error;

		//
		//	create index buffer
		//
		glGenBuffers(1, &m_index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*m_index_count, index, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		error = glGetError();

		//
		//	create vertex buffer
		//
		glGenBuffers(1, &m_vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, buffer_size, v, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//
		//	create verex array object
		//
		glGenVertexArrays(1, &m_vertex_array);
		glBindVertexArray(m_vertex_array);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
	
		InitPointers(code, sizeof(Utility::VertexPositionTexture));

		glBindVertexArray(0);

		error = glGetError();
		return true;
	}

	bool VertexArrayObject::Create(const Utility::Vertex* cpu_buffer, int buffer_size, const unsigned* index, int vertex_count, int index_count, int vertex_size, int code)
	{
		m_index_count = index_count;

		GLenum error;

		//
		//	create index buffer
		//
		glGenBuffers(1, &m_index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*index_count, index, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		error = glGetError();

		//
		//	create vertex buffer
		//
		glGenBuffers(1, &m_vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, buffer_size, cpu_buffer, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//
		//	create verex array object
		//
		glGenVertexArrays(1, &m_vertex_array);
		glBindVertexArray(m_vertex_array);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
	
		InitPointers(code, vertex_size);

		glBindVertexArray(0);

		error = glGetError();
		return true;
	}

	void VertexArrayObject::InitPointers(int code, int vertex_size)
	{
		if (code & Utility::COMPONENT_POSITION)
		{
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vertex_size, (void*)Utility::Vertex::GetOffset(Utility::COMPONENT_POSITION));
			glEnableVertexAttribArray(0);
		}
		else
		{
			glDisableVertexAttribArray(0);
		}

		if (code & Utility::COMPONENT_NORMAL)
		{
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertex_size, (void*)Utility::Vertex::GetOffset(Utility::COMPONENT_NORMAL));
			glEnableVertexAttribArray(1);
		}
		else
		{
			glDisableVertexAttribArray(1);
		}

		if (code & Utility::COMPONENT_TEXTURE)
		{
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, vertex_size, (void*)Utility::Vertex::GetOffset(Utility::COMPONENT_TEXTURE));
			glEnableVertexAttribArray(2);
		}
		else
		{
			glDisableVertexAttribArray(2);
		}

		if (code & Utility::COMPONENT_BITANGENT)
		{
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, vertex_size, (void*)Utility::Vertex::GetOffset(Utility::COMPONENT_BITANGENT));
			glEnableVertexAttribArray(3);
		}
		else
		{
			glDisableVertexAttribArray(3);
		}

		if (code & Utility::COMPONENT_TANGENT)
		{
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, vertex_size, (void*)Utility::Vertex::GetOffset(Utility::COMPONENT_TANGENT));
			glEnableVertexAttribArray(4);
		}
		else
		{
			glDisableVertexAttribArray(4);
		}

		if (code & Utility::COMPONENT_BONE)
		{
			glVertexAttribPointer(5, 4, GL_INT  , GL_FALSE, vertex_size, (void*)Utility::Vertex::GetOffset(Utility::COMPONENT_BONE));		
			glEnableVertexAttribArray(5);
		}
		else
		{
			glDisableVertexAttribArray(5);
		}
	}
}
