#include <fstream>
#include <memory>
#include "static_geometry.h"

namespace Virtual
{
	StaticGeometry::StaticGeometry()
	{
		SetType(System::ObjectType::STATIC_GEOMETRY);
	}

	bool StaticGeometry::Save(std::ostream& stream) const
	{
		if (m_vertices.empty() || m_normals.empty() || m_faces.empty() || m_tex_coords.empty())
			throw System::PunkInvalidArgumentException(L"Can't save static geometry");

		Geometry::Save(stream);
		m_bbox.Save(stream);

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
		return true;
	}

	bool StaticGeometry::Load(std::istream& stream)
	{
		Geometry::Load(stream);
		m_bbox.Load(stream);

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
		return true;
	}

	StaticGeometry* StaticGeometry::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	StaticGeometry* StaticGeometry::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<StaticGeometry> node(new StaticGeometry);
		node->Load(stream);
		return node.release();
	}
}
