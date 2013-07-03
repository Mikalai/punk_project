#ifndef _H_PUNK_OPENGL_ARCHITECTURE_VERTEX_ARRAY_OBJECT
#define _H_PUNK_OPENGL_ARCHITECTURE_VERTEX_ARRAY_OBJECT

#include <vector>
#include "../../../common/module.h"
#include "../../../../math/bounding_box.h"
#include "../../../../math/bounding_shere.h"
#include "../../buffers/module.h"
#include "../../driver/module.h"
#include "../../attribute_configer.h"
#include "../gl_primitive_type.h"

namespace GPU
{
	namespace OpenGL
	{
		template<PrimitiveType CurrentPrimitive, typename VT>
		class VertexArrayObject2 : public Renderable
		{
		protected:
			using CurrentVertex = VT;
            VideoDriverImpl* m_driver;			
            GLuint m_index_count;
			GLuint m_vao;			
            unsigned m_vertex_size;
            bool m_was_modified;
			unsigned m_primitive_count;
            int m_vb_size;
            int m_ib_size;
            IndexBufferObject* m_index_buffer;
            VertexBufferObject* m_vertex_buffer;

		public:
            VertexArrayObject2(VideoDriver* driver)
                : m_driver(driver->impl)
                , m_index_count(0)
				, m_vao(0)
				, m_vertex_size(0)
				, m_was_modified(true)
				, m_primitive_count(0)
				, m_index_buffer(nullptr)
				, m_vertex_buffer(nullptr)
			{}

			VertexArrayObject2(const VertexArrayObject2& impl)            
                : m_driver(impl.m_driver)
                , m_vertex_buffer(impl.m_vertex_buffer)
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

			void Bind(int64_t supported_by_context) 
			{
				if (m_was_modified)
				{
					Cook();
					m_was_modified = false;
				}
				ValidateOpenGL(L"Already with error");
				glBindVertexArray(m_vao);
				ValidateOpenGL(L"Unable to bind vertex array");
				m_vertex_buffer->Bind();
				m_index_buffer->Bind();

				AttributeConfiger<CurrentVertex> p(supported_by_context);
			}

			void Unbind()
			{
				glBindVertexArray(0);
				for (int i = 0; i < 16; i++)
				{
					glDisableVertexAttribArray(i);
				}
				ValidateOpenGL(L"Unable to unbind vao");
			}

			void SetVertexBuffer(const std::vector<CurrentVertex>& vbuffer)
			{
				SetVertexBuffer(&vbuffer[0], sizeof(CurrentVertex)*vbuffer.size());
			}

			void Render()
			{
				GLenum type = PrimitiveTypeToOpenGL(CurrentPrimitive);
				glDrawElements(type, m_index_count, GL_UNSIGNED_INT, 0);
				ValidateOpenGL(L"Unable to draw elements");
			}

			void SetVertexBuffer(const void* vbuffer, int size_in_bytes)
			{
				m_vb_size = size_in_bytes;

                m_vertex_buffer = m_driver->GetVideoMemory()->AllocateVertexBuffer(size_in_bytes);
				m_vertex_buffer->Bind();
				m_vertex_buffer->CopyData(vbuffer, m_vb_size);
                m_vertex_buffer->Unbind();

				m_was_modified = true;
			}

			void SetIndexBuffer(const std::vector<unsigned>& ib)
			{
				SetIndexBuffer(&ib[0], sizeof(unsigned)*ib.size());
			}

			void SetIndexBuffer(const void* ibuffer, unsigned size)
			{	
				m_index_count = size / sizeof(unsigned);	// This code depends on Render when GL_UNSIGNED_INT used in glDrawElements*

                m_index_buffer = m_driver->GetVideoMemory()->AllocateIndexBuffer(size);
				m_index_buffer->Bind();
				m_index_buffer->CopyData(ibuffer, size);
				m_index_buffer->Unbind();

				m_was_modified = true;
				m_ib_size = size;
			}

			bool Cook()
			{	
				if (glGetError() != GL_NO_ERROR)
					throw OpenGLException(L"Error came from upper subroutine to me... Will not work");

				if (!m_vertex_buffer)
					throw OpenGLException(L"Can't create VAO due to bad vertex buffer");

				if (!m_index_buffer)
					throw OpenGLException(L"Can't create VAO due to bad index buffer");

				if (m_vao)
				{
					glDeleteVertexArrays(1, &m_vao);
					ValidateOpenGL(L"Unable to delete vao");
				}

				glGenVertexArrays(1, &m_vao);
				ValidateOpenGL(L"Unable to generate vao");
				glBindVertexArray(m_vao);
				ValidateOpenGL(L"Unable to bind vao");

				m_vertex_buffer->Bind();
				m_index_buffer->Bind();

				glBindVertexArray(0);
				ValidateOpenGL(L"Unable to unbind vao");

				return true;
			}

			void* MapVertexBuffer()
			{
				return m_vertex_buffer->Map();
			}

			const void* MapVertexBuffer() const
			{
				return m_vertex_buffer->Map();
			}

			void UnmapVertexBuffer()
			{
				m_vertex_buffer->Unmap();
			}

			void Clear()
			{
                m_driver->GetVideoMemory()->FreeVertexBuffer(m_vertex_buffer);
                m_driver->GetVideoMemory()->FreeIndexBuffer(m_index_buffer);

				if (m_vao)
				{
					glDeleteVertexArrays(1, &m_vao);
					ValidateOpenGL(L"Unable to delete vao");
				}
			}

			bool Save(std::ostream& stream) const
			{
				//if (!Renderable::Save(stream))
				//	return (out_error() << "Can't save vertex array object " << std::endl, false);

				//stream.write(reinterpret_cast<const char*>(&m_index), sizeof(m_index));
				//m_location.Save(stream);

				const_cast<VertexArrayObject2<CurrentPrimitive, CurrentVertex>*>(this)->Bind(CurrentVertex::Value());

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
				int primitive_type = CurrentPrimitive;
				stream.write(reinterpret_cast<const char*>(&primitive_type), sizeof(primitive_type));			
				stream.write(reinterpret_cast<const char*>(&m_was_modified), sizeof(m_was_modified));
				int64_t combination = CurrentVertex::Value();
				stream.write(reinterpret_cast<const char*>(&combination), sizeof(combination));
				stream.write(reinterpret_cast<const char*>(&m_primitive_count), sizeof(m_primitive_count));

				//			Clear();

				return true;
			}

			bool Load(std::istream& stream)
			{
				//if (!Renderable::Load(stream))
				//	return (out_error() << "Can't load vertex array object" << std::endl, false);

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
				PrimitiveType primitive_type;
				stream.read(reinterpret_cast<char*>(&primitive_type), sizeof(primitive_type));
				stream.read(reinterpret_cast<char*>(&m_was_modified), sizeof(m_was_modified));
				int combination;
				stream.read(reinterpret_cast<char*>(&combination), sizeof(combination));
				stream.read(reinterpret_cast<char*>(&m_primitive_count), sizeof(m_primitive_count));

				if (primitive_type != CurrentPrimitive)
				{
					out_error() << "Bad primitive format " << AsString(primitive_type) << ". Expected " << AsString(CurrentPrimitive) << "." << std::endl;
					return false;
				}

				if (combination != CurrentVertex::Value())
				{
					out_error() << "Bad vertex type format " << AsString(primitive_type) << ". Expected " << CurrentVertex::Value() << "." << std::endl;
					return false;
				}

				Cook();

				return true;
			}

            bool HasData()
            {
                return m_index_buffer != nullptr && m_vertex_buffer != nullptr;
            }

            virtual size_t GetMemoryUsage() override
            {
                size_t res = 0;
                if (m_index_buffer != 0)
                    res += m_index_buffer->GetSize();
                if (m_vertex_buffer != 0)
                    res += m_vertex_buffer->GetSize();
                return res;
            }
		};
	};
}
#endif
