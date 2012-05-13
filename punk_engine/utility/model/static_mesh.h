#ifndef _H_PUNK_UTILITY_STATIC_MESH
#define _H_PUNK_UTILITY_STATIC_MESH

#include "../config.h"
#include "vertex.h"
#include "material.h"
#include "../../math/mat4.h"

namespace System
{
	class Buffer;
}

namespace Utility
{
	class Model;

	class LIB_UTILITY StaticMesh
	{
	protected:
		unsigned m_vertex_count;
		unsigned m_index_count;
		unsigned m_vertex_buffer_size;
		unsigned m_one_vertex_size;
		int m_vertex_component;
		void* m_vb;
		unsigned* m_index;
		unsigned m_material_id;
		Math::Matrix4x4<float> m_mesh_offset;
	public:
		StaticMesh();

		void SetVertexCount(unsigned count);
		void SetIndexCount(unsigned count);
		void SetVertexBufferSize(unsigned count);
		void SetOneVertexSize(unsigned count);
		void SetVertexComponent(int vertex_component);
		void SetVertexBuffer(void* vb);
		void SetIndexBuffer(unsigned* index);
		void SetMaterialID(unsigned id);

		void* GetVertexBuffer();
		unsigned* GetIndexBuffer();
		unsigned GetIndexCount() const;
		unsigned GetVertexCount() const;
		unsigned GetVertexBufferSize() const;
		unsigned GetIndexBufferSize() const;
		unsigned GetOneVertexSize() const;

		unsigned GetMaterialID() const;

		int GetVertexComponentCode() const;

		const Math::Matrix4x4<float>& GetMeshOffset() const;
		void SetMeshOffset(const Math::Matrix4x4<float>& offset);
		void Save(System::Buffer& buffer);
		void Load(System::Buffer& buffer);

	};
}

#endif