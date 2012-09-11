#ifndef _H_PUNK_UTILITY_STATIC_MESH
#define _H_PUNK_UTILITY_STATIC_MESH

#include "../config.h"
#include "../utility/model/vertex.h"
#include "material.h"
#include "../math/mat4.h"

namespace System
{
	class Buffer;
}

namespace Utility
{
	class Model;

	enum PrimitiveType { PRIMITIVE_TYPE_POINT = 0, PRIMITIVE_TYPE_LINE = 1, PRIMITIVE_TYPE_TRIANGLE = 4};

	class PUNK_ENGINE StaticMesh
	{
	protected:
		unsigned m_vertex_count;
		unsigned m_index_count;
		unsigned m_index_buffer_size;
		unsigned m_vertex_buffer_size;
		unsigned m_one_vertex_size;
		int m_vertex_component;
		std::vector<char> m_vb;
		std::vector<char> m_index;
		unsigned m_material_id;		
		Math::Matrix4x4<float> m_mesh_offset;
		PrimitiveType m_primitive_type;
	public:
		StaticMesh();

		void SetIndexCount(unsigned count) { m_index_count = count; }
		void SetVertexCount(unsigned count);
		void SetOneVertexSize(unsigned count);
		void SetVertexComponent(int vertex_component);
		void SetVertexBuffer(void* vb, int size_in_bytes);
		void SetIndexBuffer(void* ib, int size_in_bytes);
		void SetMaterialID(unsigned id);
		void SetPrimitiveType(PrimitiveType type) { m_primitive_type = type; }

		void* GetVertexBuffer();
		void* GetIndexBuffer();
		unsigned GetIndexCount() const;
		unsigned GetVertexCount() const;
		unsigned GetVertexBufferSize() const;
		unsigned GetIndexBufferSize() const;
		unsigned GetOneVertexSize() const;
		PrimitiveType GetPrimitiveType() const { return m_primitive_type; }
		unsigned GetMaterialID() const;

		int GetVertexComponentCode() const;

		const Math::Matrix4x4<float>& GetMeshOffset() const;
		void SetMeshOffset(const Math::Matrix4x4<float>& offset);

		void Save(std::ostream& stream);
		void Load(std::istream& stream);

	};
}

#endif