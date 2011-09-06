#ifndef _H_PUNK_VERTEX_ARRAY_OBJECT
#define _H_PUNK_VERTEX_ARRAY_OBJECT

#include "gl/gl3.h"
#include "config.h"

namespace Utility
{
	struct Vertex;
}

namespace OpenGL
{
	class ShaderProgram;

	class LIB_OPENGL VertexArrayObject
	{						
		GLuint m_vertex_buffer;		
		GLuint m_index_buffer;
		GLuint m_vertex_array;
		GLuint m_index_count;

	private:
		void InitPointers(int code, int vertex_size);

	public:
		~VertexArrayObject();
		void Bind() const;
		void Unbind() const;
		int GetIndexCount() const;
		void Render();
		bool Create(const Utility::Vertex* cpu_buffer, int buffer_size, const unsigned* index, int vertex_count, int index_count, int vertex_size, int code);
		bool CreateQuad();
	};
}

#endif