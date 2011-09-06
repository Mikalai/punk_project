#ifndef _H_PUNK_UTILITY_STATIC_MESH
#define _H_PUNK_UTILITY_STATIC_MESH

#include "../config.h"
#include "vertex.h"

namespace System
{
	class Buffer;
}

namespace Utility
{
	class Model;

	class LIB_UTILITY StaticMesh
	{
		unsigned m_vertex_count;
		unsigned m_index_count;
		unsigned m_vertex_buffer_size;
		unsigned m_one_vertex_size;
		int m_vertex_component;
		Vertex* m_vb;
		unsigned* m_index;
	public:
		StaticMesh();
		Vertex* GetVertexBuffer();
		unsigned* GetIndexBuffer();
		unsigned GetIndexCount() const;
		unsigned GetVertexCount() const;
		unsigned GetVertexBufferSize() const;
		unsigned GetIndexBufferSize() const;
		unsigned GetOneVertexSize() const;
		int GetVertexComponentCode() const;

		void Save(System::Buffer& buffer);
		void Load(System::Buffer& buffer);

		friend class Model;
	};
}

#endif