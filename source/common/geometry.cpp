#include "geometry.h"
#include "../system/system.h"
#include "logger.h"

namespace Common
{
	const void* StaticGeometry::GetIndexBuffer() const
	{
		return m_index;
	}

	int StaticGeometry::GetIndexCount() const
	{
		return m_index_count;
	}

	int StaticGeometry::GetIndexSize() const
	{
		return sizeof(unsigned short);
	}

	int StaticGeometry::GetIndexBufferSize() const
	{
		return GetIndexSize() * m_index_count;
	}

	const void* StaticGeometry::GetVertexBuffer() const
	{
		return m_vertex_buffer;
	}

	int StaticGeometry::GetVertexSize() const
	{
		return sizeof(Vertex);
	}

	int StaticGeometry::GetVertexBufferSize() const
	{
		return GetVertexSize() * m_vertex_count;
	}

	int StaticGeometry::GetVertexCount() const
	{
		return m_vertex_count;
	}

	int StaticGeometry::GetPositionOffset() const
	{
		return Vertex::PositionOffset;
	}

	int StaticGeometry::GetNormalOffset() const
	{
		return Vertex::NormalOffset;
	}

	int StaticGeometry::GetTextureCoordOffset() const
	{
		return Vertex::TextureCoordOffset;
	}

	int StaticGeometry::GetVertexFlagsOffset() const
	{
		return Vertex::FlagsOffset;
	}

	StaticGeometry::StaticGeometry()
	{
		m_vertex_buffer = 0;
		m_index = 0;
		m_vertex = 0;
		m_normal = 0;
		m_texture_coord = 0;
	}

	void StaticGeometry::Set(Vertex* vertex_buffer, int vertex_count, unsigned short* index_buffer, int index_count)
	{
		Clear();

		m_vertex_buffer = new Vertex[vertex_count];
		memcpy(m_vertex_buffer, vertex_buffer, sizeof(Vertex)*vertex_count);
		m_vertex_count = vertex_count;
		m_index = new unsigned short[index_count];
		memcpy(m_index, index_buffer, sizeof(unsigned short)*index_count);
		m_index_count = index_count;
	}

	bool StaticGeometry::Load(const wchar_t* filename)
	{
		Clear();

		System::string word;
		System::Buffer buffer;
		if (!System::BinaryFile::Load(filename, buffer))
			throw System::Exception(L"Unable to load a file " + System::string(filename));

		if (!Parse(buffer))
			throw System::Exception(L"Unable to parse " + System::string(filename));

		return true;
	}

	bool StaticGeometry::Load(System::Buffer& buffer)
	{
		throw System::Exception(L"Not implemented " + LOG_LOCATION_STRING);
	}

	bool StaticGeometry::ReadBoundingBox(System::Buffer& buffer)
	{
		System::string token;
		buffer.ReadWord();
		for (int i = 0; i < 8; i++)
		{
			m_bbox[i][0] = buffer.ReadWord().ToFloat();
			m_bbox[i][1] = buffer.ReadWord().ToFloat();
			m_bbox[i][2] = buffer.ReadWord().ToFloat();
		}
		return true;
	}

	bool StaticGeometry::ReadWorldMatrix(System::Buffer& buffer)
	{
		buffer.ReadWord();
		for (int i = 0; i < 12; i++)
		{
			buffer.ReadWord();
		}
		return true;
	}

	bool StaticGeometry::ReadLocalMatrix(System::Buffer& buffer)
	{
		buffer.ReadWord();
		for (int i = 0; i < 12; i++)
		{
			buffer.ReadWord();
		}
		return true;
	}

	bool StaticGeometry::ReadLocation(System::Buffer& buffer)
	{
		buffer.ReadWord();
		for (int i = 0; i < 3; i++)
		{
			buffer.ReadWord();
		}
		return true;
	}

	bool StaticGeometry::ReadFaces(System::Buffer& buffer)
	{
		buffer.ReadWord();

		while (1)
		{
			System::string token = buffer.ReadWord();
			if (token == L"{")
			{		
			}
			else if (token == L"}")
				return true;
			else if (token == L"*vertex_positions_id")
			{
				buffer.ReadWord();

				for (int i = 0; i < m_index_count/3; i++)
				{
					buffer.ReadWord();
					m_index[3*i + 0] = buffer.ReadWord().ToInt32();
					m_index[3*i + 1] = buffer.ReadWord().ToInt32();
					m_index[3*i + 2] = buffer.ReadWord().ToInt32();
				}

				buffer.ReadWord();
			}
			else
			{
				m_index_count = token.ToInt32()*3;
				m_index = new unsigned short int[m_index_count];
			}
		}

		buffer.ReadWord();
	}

	bool StaticGeometry::ReadMesh(System::Buffer& buffer)
	{
		while (1)
		{
			System::string token = buffer.ReadWord();
			if (token == L"{")
			{
			}
			if (token == L"}")
				return true;
			if (token == L"*vertex_position")
			{
				ReadVertexPosition(buffer);
				continue;
			}
			if (token == L"*normals")
			{
				ReadVertexNormal(buffer);
				continue;
			}
			if (token == L"*faces")
			{
				ReadFaces(buffer);
				continue;
			}
			if (token == L"*tex_coord")
			{
				ReadTexCoord(buffer);
				continue;
			}
		}
	}

	bool StaticGeometry::ReadTexCoord(System::Buffer& buffer)
	{
		buffer.ReadWord();

		int totalCount = m_index_count;
		m_texture_coord = new float[2 * totalCount];
		for (int i = 0; i < m_index_count/3; i++)
		{
			m_texture_coord[6*i + 0] = buffer.ReadWord().ToFloat();
			m_texture_coord[6*i + 1] = buffer.ReadWord().ToFloat();

			m_texture_coord[6*i + 2] = buffer.ReadWord().ToFloat();
			m_texture_coord[6*i + 3] = buffer.ReadWord().ToFloat();

			m_texture_coord[6*i + 4] = buffer.ReadWord().ToFloat();
			m_texture_coord[6*i + 5] = buffer.ReadWord().ToFloat();

			buffer.ReadWord();
			buffer.ReadWord();
		}

		buffer.ReadWord();

		return true;
	}

	bool StaticGeometry::ReadVertexPosition(System::Buffer& buffer)
	{
		buffer.ReadWord();

		m_vertex_count = buffer.ReadWord().ToInt32();
		m_vertex = new float[3*m_vertex_count];
		m_normal = new float[3*m_vertex_count];
		for (int i = 0; i < m_vertex_count; i++)
		{
			buffer.ReadWord();
			m_vertex[3*i + 0] = buffer.ReadWord().ToFloat();
			m_vertex[3*i + 1] = buffer.ReadWord().ToFloat();
			m_vertex[3*i + 2] = buffer.ReadWord().ToFloat();
		}

		buffer.ReadWord();

		return true;
	}

	bool StaticGeometry::ReadVertexNormal(System::Buffer& buffer)
	{
		buffer.ReadWord();

		int normals_count = buffer.ReadWord().ToInt32();
		if (normals_count != m_vertex_count)
			throw System::Exception(L"Unsupported option: normals_count != vertex_count");
		for (int i = 0; i < normals_count; i++)
		{
			buffer.ReadWord();
			m_normal[3*i + 0] = buffer.ReadWord().ToFloat();
			m_normal[3*i + 1] = buffer.ReadWord().ToFloat();
			m_normal[3*i + 2] = buffer.ReadWord().ToFloat();			
		}

		buffer.ReadWord();
		return true;
	}

	bool StaticGeometry::Parse(System::Buffer& buffer)
	{
		while (1)
		{
			System::string token = buffer.ReadWord();

			if (buffer.IsEnd())
				break;

			if (token == L"*object")
			{
			}

			if (token == L"*object_name")
			{
				buffer.ReadWord();
				buffer.ReadWord();
			}

			if (token == L"*bounding_box")
			{
				ReadBoundingBox(buffer);
			}

			if (token == L"*location")
			{
				ReadLocation(buffer);
			}

			if (token == L"*world_matrix")
			{
				ReadWorldMatrix(buffer);
			}

			if (token == L"*mesh")
			{
				ReadMesh(buffer);
			}

		}

		CreateVertexBufferInCPU();

		return true;
	}

	void StaticGeometry::CreateVertexBufferInCPU()
	{
		m_vertex_buffer = new Vertex[m_vertex_count];
		for (int i = 0; i < m_vertex_count; i++)
		{
			m_vertex_buffer[i].x = m_vertex[3*i+0];
			m_vertex_buffer[i].y = m_vertex[3*i+1];
			m_vertex_buffer[i].z = m_vertex[3*i+2];
			m_vertex_buffer[i].w = 0;

			m_vertex_buffer[i].nx = m_normal[3*i+0];
			m_vertex_buffer[i].ny = m_normal[3*i+1];
			m_vertex_buffer[i].nz = m_normal[3*i+2];
			m_vertex_buffer[i].nw = 0;

			m_vertex_buffer[i].u = m_texture_coord[6*i+0];
			m_vertex_buffer[i].v = m_texture_coord[6*i+1];
			m_vertex_buffer[i].s = 0;
			m_vertex_buffer[i].t = 0;
		}

	}

	void StaticGeometry::SaveBinary(System::Buffer& buffer)
	{
		buffer.WriteSigned32(m_vertex_count);
		buffer.WriteBuffer(m_vertex_buffer, sizeof(Vertex)*m_vertex_count);
		buffer.WriteUnsigned16(m_index_count);
		buffer.WriteBuffer(m_index, sizeof(unsigned short)*m_index_count);
	}

	void StaticGeometry::LoadBinary(System::Buffer& buffer)
	{
		buffer.WriteSigned32(m_vertex_count);
		buffer.WriteBuffer(m_vertex_buffer, sizeof(Vertex)*m_vertex_count);
		buffer.WriteUnsigned16(m_index_count);
		buffer.WriteBuffer(m_index, sizeof(unsigned short)*m_index_count);
	}

	void StaticGeometry::Clear()
	{
		delete[] m_vertex_buffer;
		delete[] m_index;
		delete[] m_vertex;
		delete[] m_normal;
		delete[] m_texture_coord;
	}

	StaticGeometry::~StaticGeometry()
	{
		Clear();
	}
}