#include "static_mesh.h"
#include "../../system/system.h"

namespace Utility
{
	StaticMesh::StaticMesh() : m_vb(0), m_index(0), m_vertex_count(0), m_index_count(0), m_vertex_buffer_size(0), m_one_vertex_size(0), m_vertex_component(0)
	{}

	void StaticMesh::SetIndexBuffer(unsigned* buffer)
	{
		m_index = buffer;
	}

	void StaticMesh::SetIndexCount(unsigned count)
	{
		m_index_count = count;
	}

	void StaticMesh::SetMaterialID(unsigned id)
	{
		m_material_id = id;
	}

	void StaticMesh::SetOneVertexSize(unsigned size)
	{
		m_one_vertex_size = size;
	}

	void StaticMesh::SetVertexBuffer(void* buffer)
	{
		m_vb = buffer;
	}

	void StaticMesh::SetVertexBufferSize(unsigned size)
	{
		m_vertex_buffer_size = size;
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
		return m_vb;
	}

	unsigned* StaticMesh::GetIndexBuffer()
	{
		return m_index;
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

	void StaticMesh::Save(System::Buffer& buffer)
	{
		buffer.WriteUnsigned32(m_vertex_count);
		buffer.WriteUnsigned32(m_index_count);
		buffer.WriteUnsigned32(m_vertex_buffer_size);
		buffer.WriteUnsigned32(m_one_vertex_size);
		buffer.WriteSigned32(m_vertex_component);
		buffer.WriteBuffer(m_vb, m_vertex_buffer_size);
		buffer.WriteBuffer(m_index, sizeof(unsigned)*m_index_count);
	}

	void StaticMesh::Load(System::Buffer& buffer)
	{
		m_vertex_count = buffer.ReadUnsigned32();
		m_index_count = buffer.ReadUnsigned32();
		m_vertex_buffer_size = buffer.ReadUnsigned32();
		m_one_vertex_size = buffer.ReadUnsigned32();
		m_vertex_component = buffer.ReadSigned32();
		m_vb = (void*) new char[m_vertex_buffer_size];
		buffer.ReadBuffer((void*&)m_vb, m_vertex_buffer_size);			// well, i don't know will it work
		m_index = new unsigned[sizeof(unsigned)*m_index_count];
		buffer.ReadBuffer((void*&)m_index, sizeof(unsigned)*m_index_count);
	}
}