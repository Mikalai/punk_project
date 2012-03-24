//
//	
//

#include "win32/driver_win32.h"
#include "vertex_array_object.h"
#include "shader_program.h"
#include "../../../../utility/model/vertex.h"

namespace OpenGL
{
	VertexArrayObject::VertexArrayObject()
	{
		m_primitive_type = GL_TRIANGLES;
	}

	VertexArrayObject::~VertexArrayObject()
	{
		Clear();
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

	void VertexArrayObject::Clear()
	{
		glDeleteBuffers(1, &m_index_buffer);
		glDeleteBuffers(1, &m_vertex_buffer);
		glDeleteVertexArrays(1, &m_vertex_array);
	}

	void VertexArrayObject::Render()
	{

		glBindVertexArray(m_vertex_array);

		glDrawElementsInstanced(m_primitive_type, m_index_count, GL_UNSIGNED_INT, 0, 1);

		//glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0);			

		glBindVertexArray(0);
	}

	void VertexArrayObject::Store(System::Buffer& buffer)
	{
		Bind();

		//
		//	store vertex buffer
		//
		int size;
		void * data = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);		
		buffer.WriteSigned32(size);
		buffer.WriteBuffer(data, size);
		glUnmapBuffer(GL_ARRAY_BUFFER);

		//
		//	store index buffer
		//
		data = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		buffer.WriteSigned32(size);
		buffer.WriteBuffer(data, size);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

		//
		//	store primitive type
		//
		buffer.WriteBuffer(&m_primitive_type, sizeof(m_primitive_type));

		//
		//	store index count
		//
		buffer.WriteUnsigned32(m_index_count);

		//
		//	store code that contains info about vertex components
		//
		buffer.WriteSigned32(m_code);

		buffer.WriteUnsigned32(m_vertex_size);
		Unbind();
	}

	void VertexArrayObject::Restore(System::Buffer& buffer)
	{
		//
		//	restore vertex buffer
		//
		int vsize, isize;
		vsize = buffer.ReadSigned32();
		unsigned char* vb = new unsigned char[vsize];
		buffer.ReadBuffer(vb, vsize);

		//
		//	restore index buffer
		//		
		isize = buffer.ReadSigned32();
		unsigned char* ib = new unsigned char[isize];
		buffer.ReadBuffer(ib, isize);

		//
		//	restore primitive type
		//
		buffer.ReadBuffer(&m_primitive_type, sizeof(m_primitive_type));

		//
		//	restore index count
		//
		m_index_count = buffer.ReadUnsigned32();

		//
		//	restore code
		//
		m_code = buffer.ReadSigned32();

		m_vertex_size = buffer.ReadUnsigned32();

		Clear();
		Create(vb, vsize, ib, isize);
	}

	bool VertexArrayObject::CreateSinglePoint()
	{
		Utility::VertexPosition v[1];
		v[0].x = v[0].y = v[0].z = v[0].w = 0;
		int buffer_size = sizeof(v);
		unsigned index[] = {0};
		m_index_count = 0;
		m_code = Utility::COMPONENT_POSITION;
		m_primitive_type = GL_POINTS;
		m_vertex_size = sizeof(Utility::VertexPosition);

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
	
		InitPointers<Utility::VertexPosition>(m_code);

		glBindVertexArray(0);

		error = glGetError();

		return true;
	}

	void VertexArrayObject::Create(void* vb, unsigned vsize, void* ib, unsigned isize)
	{
		GLenum error;

		//
		//	create index buffer
		//
		glGenBuffers(1, &m_index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, ib, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		error = glGetError();

		//
		//	create vertex buffer
		//
		glGenBuffers(1, &m_vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, vsize, vb, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//
		//	create verex array object
		//
		glGenVertexArrays(1, &m_vertex_array);
		glBindVertexArray(m_vertex_array);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
	
		InitPointers<Utility::VertexPositionNormalTextureTangentBitangentBone>(m_code);

		glBindVertexArray(0);

		error = glGetError();
	}

	bool VertexArrayObject::CreateQuad()
	{
		Utility::VertexPositionTexture v[4];
		memset(v, 0, sizeof(v));
		v[0].x = 0; v[0].y = 0; v[0].u = 0; v[0].v = 1;
		v[1].x = 0; v[1].y = 1; v[1].u = 0; v[1].v = 0;
		v[2].x = 1; v[2].y = 1; v[2].u = 1; v[2].v = 0;
		v[3].x = 1; v[3].y = 0; v[3].u = 1; v[3].v = 1;

		int buffer_size = sizeof(v);
		unsigned index[] = {0, 1, 2, 2, 3, 0};
		m_index_count = 6;
		m_code = Utility::COMPONENT_POSITION | Utility::COMPONENT_TEXTURE;
		m_vertex_size = sizeof(Utility::VertexPositionTexture);

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
	
		InitPointers<Utility::VertexPositionTexture>(m_code);

		glBindVertexArray(0);

		error = glGetError();
		return true;
	}

	bool VertexArrayObject::Create(const Utility::Vertex* cpu_buffer, int buffer_size, const unsigned* index, int vertex_count, int index_count, int vertex_size, int code)
	{
		m_index_count = index_count;
		m_code = code;
		m_vertex_size = vertex_size;
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
	
		InitPointers<Utility::VertexPositionNormalTextureTangentBitangentBone>(code);

		glBindVertexArray(0);

		error = glGetError();
		return true;
	}

	template<class T>
	inline void VertexArrayObject::InitPointers(int code)
	{
		if (code & Utility::COMPONENT_POSITION)
		{
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)Utility::Offset::Get<T>(Utility::COMPONENT_POSITION));
			glEnableVertexAttribArray(0);
		}
		else
		{
			glDisableVertexAttribArray(0);
		}

		if (code & Utility::COMPONENT_NORMAL)
		{
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)Utility::Offset::Get<T>(Utility::COMPONENT_NORMAL));
			glEnableVertexAttribArray(1);
		}
		else
		{
			glDisableVertexAttribArray(1);
		}

		if (code & Utility::COMPONENT_TEXTURE)
		{
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)Utility::Offset::Get<T>(Utility::COMPONENT_TEXTURE));
			glEnableVertexAttribArray(2);
		}
		else
		{
			glDisableVertexAttribArray(2);
		}

		if (code & Utility::COMPONENT_BITANGENT)
		{
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)Utility::Offset::Get<T>(Utility::COMPONENT_BITANGENT));
			glEnableVertexAttribArray(3);
		}
		else
		{
			glDisableVertexAttribArray(3);
		}

		if (code & Utility::COMPONENT_TANGENT)
		{
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)Utility::Offset::Get<T>(Utility::COMPONENT_TANGENT));
			glEnableVertexAttribArray(4);
		}
		else
		{
			glDisableVertexAttribArray(4);
		}

		if ((code & Utility::COMPONENT_BONE_ID) && (code & Utility::COMPONENT_BONE_WEIGHT))
		{
			glVertexAttribPointer(5, 4, GL_FLOAT  , GL_FALSE, m_vertex_size, (void*)Utility::Offset::Get<T>(Utility::COMPONENT_BONE_ID));		
			glVertexAttribPointer(6, 4, GL_FLOAT  , GL_FALSE, m_vertex_size, (void*)Utility::Offset::Get<T>(Utility::COMPONENT_BONE_WEIGHT));		
			glEnableVertexAttribArray(5);
			glEnableVertexAttribArray(6);
		}
		else
		{
			glDisableVertexAttribArray(5);
			glDisableVertexAttribArray(6);
		}
	}
}
