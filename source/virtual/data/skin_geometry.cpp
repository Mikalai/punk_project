#include "skin_geometry.h"

namespace Virtual
{
	SkinGeometry::SkinGeometry()
	{
		SetType(System::ObjectType::SKIN_GEOMETRY);
	}

	bool SkinGeometry::Save(std::ostream& stream) const
	{
		if (m_vertices.empty() || m_normals.empty() || m_faces.empty() || m_tex_coords.empty() || m_bone_weights.empty())
			throw System::PunkInvalidCastException(L"Can't save static geometry");

		if (!Geometry::Save(stream))
			throw System::PunkInvalidCastException(L"Can't save static geometry");
	
		if (!m_bbox.Save(stream))
			throw System::PunkInvalidCastException(L"Can't save static geometry");

		int size = (int)m_vertices.size();		
		stream.write((char*)&size, sizeof(size));
		stream.write((char*)&m_vertices[0], sizeof(m_vertices[0])*size);
		size = (int)m_faces.size();
		stream.write((char*)&size, sizeof(size));
		stream.write((char*)&m_faces[0], sizeof(m_faces[0])*size);
		size = (int)m_normals.size();
		stream.write((char*)&size, sizeof(size));
		stream.write((char*)&m_normals[0], sizeof(m_normals[0])*size);
		int count = (int)m_tex_coords.size();
		stream.write((char*)&count, sizeof(count));
		for (auto it = m_tex_coords.begin(); it != m_tex_coords.end(); ++it)
		{
			it->first.Save(stream);
			size = (int)it->second.size();
			stream.write((char*)&size, sizeof(size));
			stream.write((char*)&it->second[0], sizeof(it->second[0]) * size);
		}

		count = m_bone_weights.size();
		stream.write((char*)&count, sizeof(count));
		for each (auto it in m_bone_weights)
		{
			int index = it.first;
			stream.write((char*)&index, sizeof(index));
			int count = it.second.size();
			stream.write((char*)&count, sizeof(count));
			for each (auto it2 in it.second)
			{
				it2.first.Save(stream);
				float weight = it2.second;
				stream.write((char*)&weight, sizeof(weight));
			}
		}

		return true;
	}

	bool SkinGeometry::Load(std::istream& stream)
	{
		if (!Geometry::Load(stream))
			throw System::PunkInvalidCastException(L"Can't save static geometry");
	
		if (!m_bbox.Load(stream))
			throw System::PunkInvalidCastException(L"Can't load static geometry");

		int size = 0;
		stream.read((char*)&size, sizeof(size));
		m_vertices.resize(size);
		stream.read((char*)&m_vertices[0], sizeof(m_vertices[0])*size);
		
		size = 0;
		stream.read((char*)&size, sizeof(size));
		m_faces.resize(size);
		stream.read((char*)&m_faces[0], sizeof(m_faces[0])*size);

		size = 0;
		stream.read((char*)&size, sizeof(size));
		m_normals.resize(size);
		stream.read((char*)&m_normals[0], sizeof(m_normals[0])*size);

		int count = 0;
		stream.read((char*)&count, sizeof(count));
		for (int i = 0; i < count; ++i)
		{
			System::string name;
			name.Load(stream);
			size = 0;
			stream.read((char*)&size, sizeof(size));
			std::vector<Math::Vector4<Math::vec2>> v;
			v.resize(size);
			stream.read((char*)&v[0], sizeof(v[0]) * size);
			m_tex_coords[name] = v;
		}

		count = 0;
		stream.read((char*)&count, sizeof(count));
		for (int i = 0; i < count; ++i)
		{
			int index = 0;
			stream.read((char*)&index, sizeof(index));
			int num_bones = 0;
			stream.read((char*)&num_bones, sizeof(num_bones));
			for (int j = 0; j < num_bones; ++j)
			{
				System::string name;
				name.Load(stream);
				float weight = 0;
				stream.read((char*)&weight, sizeof(weight));
				m_bone_weights[index][name] = weight;
			}
		}

		return true;
	}

	SkinGeometry* SkinGeometry::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	SkinGeometry* SkinGeometry::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<SkinGeometry> node(new SkinGeometry);
		node->Load(stream);
		return node.release();
	}

	void SkinGeometry::DropCache() 
	{ 
		safe_delete(m_cache.m_gpu_buffer);
	}
	
	bool SkinGeometry::IsCacheValid() 
	{ 
		return m_cache.m_gpu_buffer != nullptr; 
	}

	void SkinGeometry::SetGPUBufferCache(Object* value)
	{ 
		if (m_cache.m_gpu_buffer)
			safe_delete(m_cache.m_gpu_buffer);
		m_cache.m_gpu_buffer = value; 
	}

}