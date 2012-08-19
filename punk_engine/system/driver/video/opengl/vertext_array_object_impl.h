#ifndef _H_PUNK_OPENGL_VERTEXT_ARRAY_OBJECT_IMPL
#define _H_PUNK_OPENGL_VERTEXT_ARRAY_OBJECT_IMPL

#include <ostream>
#include <istream>
#include "gl/gl3.h"
#include "config.h"
#include "../../../buffer.h"
#include "extensions.h"
#include "../../../error.h"
#include "vertex_attributes.h"
#include "../../../../utility/model/static_mesh.h"

namespace OpenGL
{


	struct VertexArrayObjectImpl
	{
		int m_index;
		System::string m_location;
		GLuint m_vertex_buffer;		
		GLuint m_index_buffer;
		GLuint m_vao;
		GLuint m_index_count;
		GLenum m_primitive_type;
		unsigned m_vertex_size;		
		bool m_was_modified;
		VertexAttributes m_combination;
		unsigned m_primitive_count;
		int m_vb_size;
		int m_ib_size;
		Math::BoundingBox m_bbox;
		Math::mat4 m_mesh_transform;

		VertexArrayObjectImpl()
			: m_vertex_buffer(0)
			, m_index_buffer(0)
			, m_index_count(0)
			, m_vao(0)
			, m_primitive_type(GL_TRIANGLES)
			, m_vertex_size(0)
			, m_was_modified(m_was_modified)
			, m_combination(0)
			, m_primitive_count(0)
		{}

		VertexArrayObjectImpl(const VertexArrayObjectImpl& impl)
			: m_vertex_buffer(impl.m_vertex_buffer)
			, m_index_buffer(impl.m_index_buffer)
			, m_index_count(impl.m_index_count)
			, m_vao(impl.m_vao)
			, m_primitive_type(impl.m_primitive_type)
			, m_vertex_size(impl.m_vertex_size)
			, m_was_modified(impl.m_was_modified)
			, m_combination(impl.m_combination)
			, m_primitive_count(impl.m_primitive_count)
		{}

		~VertexArrayObjectImpl()
		{
			Clear();
		}

		void SetIndex(int index)
		{
			m_index = index;
		}

		int GetIndex() const
		{
			return m_index;
		}

		void SetSourceFile(const System::string& filename)
		{
			m_location = filename;
		}

		const System::string& GetSourceFile() const
		{
			return m_location;
		}

		void SetMeshTransform(const Math::mat4& value)
		{
			m_mesh_transform = value;
		}

		const Math::mat4& GetMeshTransform() const
		{
			return m_mesh_transform;
		}

		void Bind(VertexAttributes supported_by_context)
		{
			if (m_was_modified)
			{
				Cook(m_combination, m_primitive_type);
				m_was_modified = false;
			}
			CHECK_GL_ERROR(L"Already with error");
			glBindVertexArray(m_vao);
			CHECK_GL_ERROR(L"Unable to bind vertex array");
			glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
			CHECK_GL_ERROR(L"Unable to bind vertex buffer");
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
			CHECK_GL_ERROR(L"Unable to bind index buffer");
			SetUpAttributes(supported_by_context);			
		}

		void Unbind()
		{
			glBindVertexArray(0);
			CHECK_GL_ERROR(L"Unable to unbind vao");
		}

		void SetVertexBuffer(const void* vbuffer, unsigned buffer_size, unsigned vertex_size)
		{
			if (m_vertex_buffer)
			{
				glDeleteBuffers(1, &m_vertex_buffer);
				CHECK_GL_ERROR(L"Unable to delete vertex buffer");
			}
			glBindVertexArray(0);
			CHECK_GL_ERROR(L"Unable to generate vertex buffer");
			glGenBuffers(1, &m_vertex_buffer);
			CHECK_GL_ERROR(L"Unable to generate vertex buffer");
			glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
			CHECK_GL_ERROR(L"Unable to bind vertex buffer");
			glBufferData(GL_ARRAY_BUFFER, buffer_size, vbuffer, GL_STATIC_DRAW);
			CHECK_GL_ERROR(L"Unable to fill vertex buffer with data");
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			CHECK_GL_ERROR(L"Unable to unbind vertex buffer");
			m_vertex_size = vertex_size;
			m_was_modified = true;
			glBindVertexArray(0);
			CHECK_GL_ERROR(L"Unable to generate vertex buffer");
			m_vb_size = buffer_size;

			m_bbox.Create(reinterpret_cast<const float*>(vbuffer), m_vertex_size, m_vb_size/m_vertex_size);
		}

		void SetUpAttributes(VertexAttributes supported_by_context)
		{
			// We should enable only those attributes that are supported by context and available in vertex buffer
			VertexAttributes components = m_combination & supported_by_context;

			for (int i = 0; i < 6; ++i)
			{
				glDisableVertexAttribArray(i);
				CHECK_GL_ERROR(L"Unable to disable one of 16 vertex attrib arrays");
			}

			if (components == VERTEX_POSITION)
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (VERTEX_POSITION|VERTEX_NORMAL))
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (VERTEX_POSITION|VERTEX_TEXTURE_0|VERTEX_NORMAL|VERTEX_FLAGS))
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(2*4*sizeof(float)));	//	texture
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(3*4*sizeof(float)));	//	flags
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(6);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (VERTEX_POSITION|VERTEX_TEXTURE_0))
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(4*4*sizeof(float)));	//	texture_0
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (VERTEX_POSITION|VERTEX_NORMAL|VERTEX_TEXTURE_0))
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(4*4*sizeof(float)));	//texture_0
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}		
			else if (components == (VERTEX_POSITION|VERTEX_NORMAL|VERTEX_TANGENT|VERTEX_BITANGENT|VERTEX_TEXTURE_0))
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(2*4*sizeof(float)));	//	tangent
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(3*4*sizeof(float)));	//	bitangent
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(4*4*sizeof(float)));	//	texture_0
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(2);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(3);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else if (components == (VERTEX_POSITION|VERTEX_NORMAL|VERTEX_TANGENT|VERTEX_BITANGENT|VERTEX_TEXTURE_0|VERTEX_BONE))
			{
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)0);	//	position
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(4*sizeof(float)));	//	normal
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(2*4*sizeof(float)));	//	tangent
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(3*4*sizeof(float)));	//	bitangent
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(4*4*sizeof(float)));	//	texture_0
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(5*4*sizeof(float)));	//	bone_id
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, m_vertex_size, (void*)(6*4*sizeof(float)));	//	bone_weight
				CHECK_GL_ERROR(L"Unable to set vertex attrib pointer vao");
				glEnableVertexAttribArray(0);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(1);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(2);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(3);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(4);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(5);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
				glEnableVertexAttribArray(6);
				CHECK_GL_ERROR(L"Unable to enable vertex attrib pointer vao");
			}
			else
			{
				throw System::SystemError(L"Unsupported components combination of vertex");
			}
		}

		void SetPrimitiveType(int type)
		{
			m_primitive_type = type;
		}

		void SetIndexBuffer(const void* ibuffer, unsigned size)
		{
			if (m_index_buffer)
			{
				glDeleteBuffers(1, &m_index_buffer);
				CHECK_GL_ERROR(L"Unable to delete index buffer");
			}
			glBindVertexArray(0);
			CHECK_GL_ERROR(L"Unable to generate vertex buffer");
			glGenBuffers(1, &m_index_buffer);
			CHECK_GL_ERROR(L"Unable to generate index buffer");
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
			CHECK_GL_ERROR(L"Unable to bind index buffer");
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, ibuffer, GL_STATIC_DRAW);
			CHECK_GL_ERROR(L"Unable to fill index buffer with data");
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			CHECK_GL_ERROR(L"Unable to unbind index buffer");
			m_index_count = size / sizeof(unsigned);	// This code depends on Render when GL_UNSIGNED_INT used in glDrawElements*
			m_was_modified = true;
			glBindVertexArray(0);
			CHECK_GL_ERROR(L"Unable to generate vertex buffer");
			m_ib_size = size;
		}

		void Cook(VertexAttributes components, GLenum primitive_type)
		{	
			if (glGetError() != GL_NO_ERROR)
				throw System::SystemError(L"Error came from upper subroutine to me... Will not work");
			if (!m_vertex_buffer)
				throw System::SystemError(L"Can't create VAO due to bad vertex buffer");
			if (!m_index_buffer)
				throw System::SystemError(L"Can't create VAO due to bad index buffer");

			if (m_vao)
			{
				glDeleteVertexArrays(1, &m_vao);
				CHECK_GL_ERROR(L"Unable to delete vao");
			}
			glGenVertexArrays(1, &m_vao);
			CHECK_GL_ERROR(L"Unable to generate vao");
			glBindVertexArray(m_vao);
			CHECK_GL_ERROR(L"Unable to bind vao");
			glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
			CHECK_GL_ERROR(L"Unable to bind vertex buffer to vao");
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
			CHECK_GL_ERROR(L"Unable to bind index buffer to vao");			

			glBindVertexArray(0);
			CHECK_GL_ERROR(L"Unable to unbind vao");

			m_combination = components;	
			switch (m_primitive_type = primitive_type)
			{
			case GL_POINTS:
				m_primitive_count = m_index_count;
				break;
			case GL_LINES:
				m_primitive_count = m_index_count / 2;
				break;
			case GL_TRIANGLES:
				m_primitive_count = m_index_count / 3;
				break;
			default:
				throw System::SystemError(L"Unsupported primitive type");
			}
		}

		void* MapVertexBuffer()
		{
			glBindVertexArray(m_vao);
			CHECK_GL_ERROR(L"Unable to bind vao");
			GLvoid* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
			CHECK_GL_ERROR(L"Unable to map buffer");
			glBindVertexArray(0);
			CHECK_GL_ERROR(L"Unable to unbind vao");
			return buffer;
		}

		const void* MapVertexBuffer() const
		{
			glBindVertexArray(m_vao);
			CHECK_GL_ERROR(L"Unable to bind vao");
			GLvoid* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
			CHECK_GL_ERROR(L"Unable to map buffer");
			glBindVertexArray(0);
			CHECK_GL_ERROR(L"Unable to unbind vao");
			return buffer;			
		}

		void UnmapVertexBuffer()
		{
			glBindVertexArray(m_vao);
			CHECK_GL_ERROR(L"Unable to bind vao");
			glUnmapBuffer(GL_ARRAY_BUFFER);
			CHECK_GL_ERROR(L"Unable to map buffer");
			glBindVertexArray(0);
			CHECK_GL_ERROR(L"Unable to unbind vao");
		}

		void Clear()
		{
			if (m_vertex_buffer)
			{
				glDeleteBuffers(1, &m_vertex_buffer);
				CHECK_GL_ERROR(L"Unable to delete vertext buffer");
			}
			if (m_index_buffer)
			{
				glDeleteBuffers(1, &m_index_buffer);
				CHECK_GL_ERROR(L"Unable to delete index buffer");
			}
			if (m_vao)
			{
				glDeleteVertexArrays(1, &m_vao);
				CHECK_GL_ERROR(L"Unable to delete vao");
			}
		}

		void Save(std::ostream& stream)
		{
			//stream.write(reinterpret_cast<const char*>(&m_index), sizeof(m_index));
			//m_location.Save(stream);

			Bind(m_combination);

			GLvoid* vb = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
			stream.write(reinterpret_cast<const char*>(&m_vb_size), sizeof(m_vb_size));
			stream.write(reinterpret_cast<const char*>(vb), m_vb_size);			
			stream.write(reinterpret_cast<const char*>(&m_vertex_size), sizeof(m_vertex_size));		
			glUnmapBuffer(GL_ARRAY_BUFFER);

			GLvoid* ib = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
			stream.write(reinterpret_cast<const char*>(&m_ib_size), sizeof(m_ib_size));
			stream.write(reinterpret_cast<const char*>(ib), m_ib_size);
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		
			stream.write(reinterpret_cast<const char*>(&m_index_count), sizeof(m_index_buffer));
			stream.write(reinterpret_cast<const char*>(&m_primitive_type), sizeof(m_primitive_type));			
			stream.write(reinterpret_cast<const char*>(&m_was_modified), sizeof(m_was_modified));
			stream.write(reinterpret_cast<const char*>(&m_combination), sizeof(m_combination));
			stream.write(reinterpret_cast<const char*>(&m_primitive_count), sizeof(m_primitive_count));
			stream.write(reinterpret_cast<const char*>(&m_mesh_transform[0]), sizeof(m_mesh_transform));

			Clear();
		}

		void Load(std::istream& stream)
		{
			//stream.read(reinterpret_cast<char*>(&m_index), sizeof(m_index));
			//m_location.Load(stream);
			stream.read(reinterpret_cast<char*>(&m_vb_size), sizeof(m_vb_size));
			char* vb = new char[m_vb_size];
			try
			{
				stream.read(reinterpret_cast<char*>(vb), m_vb_size);
				stream.read(reinterpret_cast<char*>(&m_vertex_size), sizeof(m_vertex_size));					
				SetVertexBuffer(vb, m_vb_size, m_vertex_size);
			}
			catch(...)
			{
				delete[] vb;
				throw;
			}
			delete[] vb;

			stream.read(reinterpret_cast<char*>(&m_ib_size), sizeof(m_ib_size));
			char* ib = new char[m_ib_size];
			try
			{
				stream.read(reinterpret_cast<char*>(ib), m_ib_size);
				SetIndexBuffer(ib, m_ib_size);
			}
			catch(...)
			{
				delete[] ib;
				throw;
			}
			delete[] ib;
		
			stream.read(reinterpret_cast<char*>(&m_index_count), sizeof(m_index_buffer));
			stream.read(reinterpret_cast<char*>(&m_primitive_type), sizeof(m_primitive_type));
			stream.read(reinterpret_cast<char*>(&m_was_modified), sizeof(m_was_modified));
			stream.read(reinterpret_cast<char*>(&m_combination), sizeof(m_combination));
			stream.read(reinterpret_cast<char*>(&m_primitive_count), sizeof(m_primitive_count));
			stream.read(reinterpret_cast<char*>(&m_mesh_transform[0]), sizeof(m_mesh_transform));

			Cook(m_combination, m_primitive_type);
		}

		Math::BoundingBox& GetBoundingBox()
		{
			return m_bbox;
		}

		const Math::BoundingBox& GetBoundingBox() const
		{
			return m_bbox;
		}
	};
}

#endif