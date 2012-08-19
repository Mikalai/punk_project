#include "static_mesh.h"
#include "../../system/system.h"

namespace Utility
{
	StaticMesh::StaticMesh() 
		: m_vb(0)
		, m_index(0)
		, m_vertex_count(0)
		, m_index_count(0)
		, m_vertex_buffer_size(0)
		, m_one_vertex_size(0)
		, m_vertex_component(0)
		, m_primitive_type(PRIMITIVE_TYPE_TRIANGLE)
	{}

	void StaticMesh::SetIndexBuffer(void* buffer, int size_in_bytes)
	{
		m_index_buffer_size = size_in_bytes;
		m_index.resize(size_in_bytes);
		if (buffer)
			memcpy(&m_index[0], buffer, size_in_bytes);
	}

	void StaticMesh::SetMaterialID(unsigned id)
	{
		m_material_id = id;
	}

	void StaticMesh::SetOneVertexSize(unsigned size)
	{
		m_one_vertex_size = size;
	}

	void StaticMesh::SetVertexBuffer(void* buffer, int size_in_bytes)
	{
		m_vertex_buffer_size = size_in_bytes;
		m_vb.resize(size_in_bytes);
		if (buffer)
			memcpy(&m_vb[0], buffer, size_in_bytes);
	}

	void StaticMesh::SetVertexComponent(int component)
	{
		m_vertex_component = component;
	}

	void StaticMesh::SetVertexCount(unsigned count)
	{
		m_vertex_count = count;
	}

	void* StaticMesh::GetVertexBuffer()
	{
		return (void*)&m_vb[0];
	}

	void* StaticMesh::GetIndexBuffer()
	{
		return (void*)&m_index[0];
	}

	unsigned StaticMesh::GetIndexCount() const
	{
		return m_index_count;
	}

	unsigned StaticMesh::GetVertexCount() const
	{
		return m_vertex_count;
	}

	unsigned StaticMesh::GetVertexBufferSize() const
	{
		return m_vertex_buffer_size;
	}

	unsigned StaticMesh::GetIndexBufferSize() const
	{
		return sizeof(unsigned)*m_index_count;
	}

	unsigned StaticMesh::GetOneVertexSize() const
	{
		return m_one_vertex_size;
	}

	unsigned StaticMesh::GetMaterialID() const
	{
		return m_material_id;
	}

	int StaticMesh::GetVertexComponentCode() const
	{
		return m_vertex_component;
	}

	void StaticMesh::SetMeshOffset(const Math::Matrix4x4<float>& m)
	{
		m_mesh_offset = m;
	}

	const Math::Matrix4x4<float>& StaticMesh::GetMeshOffset() const
	{
		return m_mesh_offset;
	}

	void StaticMesh::Save(std::ostream& stream)
	{
		stream.write(reinterpret_cast<const char*>(&m_primitive_type), sizeof(PrimitiveType));
		stream.write(reinterpret_cast<const char*>(&m_vertex_count), sizeof(m_vertex_count));
		stream.write(reinterpret_cast<const char*>(&m_index_count), sizeof(m_index_count));
		stream.write(reinterpret_cast<const char*>(&m_vertex_buffer_size), sizeof(m_vertex_buffer_size));
		stream.write(reinterpret_cast<const char*>(&m_index_buffer_size), sizeof(m_index_buffer_size));
		stream.write(reinterpret_cast<const char*>(&m_one_vertex_size), sizeof(m_one_vertex_size));
		stream.write(reinterpret_cast<const char*>(&m_vertex_component), sizeof(m_vertex_component));
		stream.write(reinterpret_cast<const char*>(&m_vb[0]), m_vertex_buffer_size);
		stream.write(reinterpret_cast<const char*>(&m_index[0]), sizeof(unsigned)*m_index_count);		
		m_mesh_offset.Save(stream);
	}

	void StaticMesh::Load(std::istream& stream)
	{
		stream.read(reinterpret_cast<char*>(&m_primitive_type), sizeof(PrimitiveType));
		stream.read(reinterpret_cast<char*>(&m_vertex_count), sizeof(m_vertex_count));
		stream.read(reinterpret_cast<char*>(&m_index_count), sizeof(m_index_count));
		stream.read(reinterpret_cast<char*>(&m_vertex_buffer_size), sizeof(m_vertex_buffer_size));
		stream.read(reinterpret_cast<char*>(&m_index_buffer_size), sizeof(m_index_buffer_size));
		stream.read(reinterpret_cast<char*>(&m_one_vertex_size), sizeof(m_one_vertex_size));
		stream.read(reinterpret_cast<char*>(&m_vertex_component), sizeof(m_vertex_component));
		m_vb.resize(m_vertex_buffer_size);
		stream.read(reinterpret_cast<char*>(&m_vb[0]), m_vertex_buffer_size);
		m_index.resize(m_index_buffer_size);
		stream.read(reinterpret_cast<char*>(&m_index[0]), m_index_buffer_size);
		m_mesh_offset.Load(stream);
	}
}