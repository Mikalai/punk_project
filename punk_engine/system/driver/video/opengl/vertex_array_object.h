#ifndef _H_PUNK_VERTEX_ARRAY_OBJECT
#define _H_PUNK_VERTEX_ARRAY_OBJECT

#include "gl/gl3.h"
#include "config.h"
#include "../../../buffer.h"

namespace Utility
{
	struct Vertex;
}

class ShaderProgram;

namespace OpenGL
{
	class MODULE_OPENGL VertexArrayObject
	{						
		GLuint m_vertex_buffer;		
		GLuint m_index_buffer;
		GLuint m_vertex_array;
		GLuint m_index_count;
		GLenum m_primitive_type;
		int m_code;
		unsigned m_vertex_size;

	private:

		template<class T>
		inline void InitPointers(int code);

		void Create(void* vertex_buffer, unsigned vsize, void* index_buffer, unsigned isize);
	public:
		VertexArrayObject();
		~VertexArrayObject();
		void Bind() const;
		void Unbind() const;
		int GetIndexCount() const;
		void Render();
		bool Create(const Utility::Vertex* cpu_buffer, int buffer_size, const unsigned* index, int vertex_count, int index_count, int vertex_size, int code);
		bool CreateQuad();
		bool CreateSinglePoint();

		void Clear();

		void Store(System::Buffer& buffer);
		void Restore(System::Buffer& buffer);
	};
}

#endif