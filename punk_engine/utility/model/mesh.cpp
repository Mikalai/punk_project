#include <istream>
#include <ostream>

#include "mesh.h"

namespace Utility
{
	void Mesh::Save(std::ostream& stream)
	{
		int size = (int)m_vertices.size();
		stream.write((char*)&size, sizeof(size));
		if (size)
			stream.write((char*)&m_vertices[0], sizeof(m_vertices[0])*size);
		
		size = (int)m_normals.size();
		stream.write((char*)&size, sizeof(size));
		if (size)
			stream.write((char*)&m_normals[0], sizeof(m_normals[0])*size);
		
		size = (int)m_faces.size();
		stream.write((char*)&size, sizeof(size));
		if (size)
			stream.write((char*)&m_faces[0], sizeof(m_faces[0])*size);

		size = (int)m_bone_weights.size();
		stream.write((char*)&size, sizeof(size));
		if (size)
		{
			for (auto it = m_bone_weights.begin(); it != m_bone_weights.end(); ++it)
			{
				stream.write((char*)&it->first, sizeof(it->first));	//	vertex index
				size = it->second.size();	//	count of bones effect this vertex
				stream.write((char*)&size, sizeof(size));
				for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
				{
					it2->first.Save(stream);	//	name of the bone
					stream.write((char*)&it2->second, sizeof(it2->second));	//	weight
				}
			}
		}		
		m_tex_coords.Save(stream);
	}

	void Mesh::Load(std::istream& stream)
	{
		int size;
		stream.read((char*)&size, sizeof(size));
		if (size)
		{
			m_vertices.resize(size);
			stream.read((char*)&m_vertices[0], sizeof(m_vertices[0])*size);
		}
		
		stream.read((char*)&size, sizeof(size));
		if (size)
		{
			m_normals.resize(size);
			stream.read((char*)&m_normals[0], sizeof(m_normals[0])*size);
		}
		
		stream.read((char*)&size, sizeof(size));
		if (size)
		{
			m_faces.resize(size);
			stream.read((char*)&m_faces[0], sizeof(m_faces[0])*size);
		}

		stream.read((char*)&size, sizeof(size));
		if (size)
		{
			for (int i = 0; i < size; ++i)
			{
				VertexIndex index;
				stream.read((char*)&index, sizeof(index));
				BoneWeights weight;
				int bone_count;
				stream.read((char*)&bone_count, sizeof(bone_count));
				for (int j = 0; j < bone_count; ++j)
				{
					System::string bone_name;
					bone_name.Load(stream);
					Weight weight;
					stream.read((char*)&weight, sizeof(weight));	//	weight
				}				
			}
		}		
		m_tex_coords.Load(stream);
	}
}