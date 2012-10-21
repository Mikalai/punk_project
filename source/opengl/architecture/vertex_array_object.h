#ifndef _H_PUNK_OPENGL_ARCHITECTURE_VERTEX_ARRAY_OBJECT
#define _H_PUNK_OPENGL_ARCHITECTURE_VERTEX_ARRAY_OBJECT

#include <vector>
#include "../../math/bounding_box.h"
#include "../attribute_configer.h"

namespace OpenGL
{
	template<int PrimitiveType, int VertexType>
	struct VertexArrayObject2
	{
		typedef Utility::Vertex<VertexType> CurrentVertex;
		GLuint m_vertex_buffer;		
		GLuint m_index_buffer;
		GLuint m_vao;
		GLuint m_index_count;
		unsigned m_vertex_size;				
		unsigned m_primitive_count;
		int m_vb_size;
		int m_ib_size;		
		Math::BoundingBox m_bbox;
		bool m_was_modified;

		VertexArrayObject2()
			: m_vertex_buffer(0)
			, m_index_buffer(0)
			, m_index_count(0)
			, m_vao(0)
			, m_vertex_size(0)
			, m_was_modified(true)
			, m_primitive_count(0)
		{}

		VertexArrayObject2(const VertexArrayObject2& impl)
			: m_vertex_buffer(impl.m_vertex_buffer)
			, m_index_buffer(impl.m_index_buffer)
			, m_index_count(impl.m_index_count)
			, m_vao(impl.m_vao)
			, m_vertex_size(impl.m_vertex_size)
			, m_was_modified(impl.m_was_modified)			
			, m_primitive_count(impl.m_primitive_count)
		{}

		~VertexArrayObject2()
		{
			Clear();
		}

		void Bind(Utility::VertexAttributes supported_by_context)
		{
			if (m_was_modified)
			{
				Cook();
				m_was_modified = false;
			}
			CHECK_GL_ERROR(L"Already with error");
			glBindVertexArray(m_vao);
			CHECK_GL_ERROR(L"Unable to bind vertex array");
			glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
			CHECK_GL_ERROR(L"Unable to bind vertex buffer");
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
			CHECK_GL_ERROR(L"Unable to bind index buffer");

			AttributeConfiger<VertexType> p(supported_by_context);			
		}

		void Unbind()
		{
			glBindVertexArray(0);
			for (int i = 0; i < 16; i++)
			{
				glDisableVertexAttribArray(i);
			}
			CHECK_GL_ERROR(L"Unable to unbind vao");
		}
		
		void SetVertexBuffer(const std::vector<CurrentVertex>& vbuffer)
		{
			SetVertexBuffer(&vbuffer[0], sizeof(CurrentVertex)*vbuffer.size());
		}

		void SetVertexBuffer(const void* vbuffer, int size_in_bytes)
		{
			m_vb_size = size_in_bytes;

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
			glBufferData(GL_ARRAY_BUFFER, m_vb_size, vbuffer, GL_STATIC_DRAW);
			CHECK_GL_ERROR(L"Unable to fill vertex buffer with data");
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			CHECK_GL_ERROR(L"Unable to unbind vertex buffer");		
			glBindVertexArray(0);
			CHECK_GL_ERROR(L"Unable to generate vertex buffer");		
			m_bbox.Create(reinterpret_cast<const float*>(vbuffer), sizeof(CurrentVertex), m_vb_size/sizeof(CurrentVertex));
			m_was_modified = true;
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

		void Cook()
		{	
			if (glGetError() != GL_NO_ERROR)
				out_error() << L"Error came from upper subroutine to me... Will not work" << std::endl;
			if (!m_vertex_buffer)
				out_error() << L"Can't create VAO due to bad vertex buffer" << std::endl;
			if (!m_index_buffer)
				out_error() << L"Can't create VAO due to bad index buffer" << std::endl;

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

		bool Save(std::ostream& stream)
		{
			//stream.write(reinterpret_cast<const char*>(&m_index), sizeof(m_index));
			//m_location.Save(stream);

			Bind(VertexType);

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
			int primitive_type = PrimitiveType;
			stream.write(reinterpret_cast<const char*>(&primitive_type), sizeof(primitive_type));			
			stream.write(reinterpret_cast<const char*>(&m_was_modified), sizeof(m_was_modified));
			int combination = VertexType;
			stream.write(reinterpret_cast<const char*>(&combination), sizeof(combination));
			stream.write(reinterpret_cast<const char*>(&m_primitive_count), sizeof(m_primitive_count));

			Clear();
		}

		bool Load(std::istream& stream)
		{
			//stream.read(reinterpret_cast<char*>(&m_index), sizeof(m_index));
			//m_location.Load(stream);
			stream.read(reinterpret_cast<char*>(&m_vb_size), sizeof(m_vb_size));
			char* vb = new char[m_vb_size];
			try
			{
				stream.read(reinterpret_cast<char*>(vb), m_vb_size);
				stream.read(reinterpret_cast<char*>(&m_vertex_size), sizeof(m_vertex_size));					
				SetVertexBuffer(vb, m_vb_size);
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
			int primitive_type;
			stream.read(reinterpret_cast<char*>(&primitive_type), sizeof(primitive_type));
			stream.read(reinterpret_cast<char*>(&m_was_modified), sizeof(m_was_modified));
			int combination;
			stream.read(reinterpret_cast<char*>(&combination), sizeof(combination));
			stream.read(reinterpret_cast<char*>(&m_primitive_count), sizeof(m_primitive_count));

			if (primitive_type != PrimitiveType)
			{
				out_error() << "Bad primitive format " << primitive_type << ". Expected " << PrimitiveType << "." << std::endl;
				return;
			}

			if (combination != VertexType)
			{
				out_error() << "Bad vertex type format " << primitive_type << ". Expected " << VertexType << "." << std::endl;
				return;
			}

			Cook();
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
};

#endif