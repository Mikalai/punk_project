//#include "../../system/logger.h"
//#include "mesh_desc.h"
//#include <ostream>
//#include <istream>

//namespace Utility
//{
//	std::wostream& MeshDesc::out_formatted(std::wostream& stream)
//	{
//		stream << Tab() << typeid(*this).name() << std::endl;
//		Tab::Inc();
//		stream << Tab() << "Vertex count: " << m_vertices.size() << std::endl;
//		stream << Tab() << "Normals count: " << m_normals.size() << std::endl;
//		stream << Tab() << "Face count: " << m_faces.size() << std::endl;
//		stream << Tab() << "Bone weights count: " << m_bone_weights.size() << std::endl;
//		stream << Tab() << "Texture coords: " << m_tex_coords.size() << std::endl;
//		for (auto texture_set : m_tex_coords)
//			stream << Tab() << "Texture vertex count: " << texture_set.second.size() << std::endl;
//		stream << Tab::Dec() << typeid(*this).name();
//		return stream;
//	}

//	bool MeshDesc::Save(std::ostream& stream) const
//	{
//		{
//			int size = (int)m_vertices.size();
//			stream.write((char*)&size, sizeof(size));
//			if (size)
//				stream.write((char*)&m_vertices[0][0], sizeof(m_vertices[0][0])*size);
//		}

//		{
//			int size = (int)m_normals.size();
//			stream.write((char*)&size, sizeof(size));
//			if (size)
//				stream.write((char*)&m_normals[0][0], sizeof(m_normals[0][0])*size);
//		}

//		{
//			int size = (int)m_faces.size();
//			stream.write((char*)&size, sizeof(size));
//			if (size)
//				stream.write((char*)&m_faces[0][0], sizeof(m_faces[0][0])*size);
//		}

//		{
//			int size = (int)m_bone_weights.size();
//			stream.write((char*)&size, sizeof(size));
//			if (size)
//			{
//				for (auto it = m_bone_weights.begin(); it != m_bone_weights.end(); ++it)
//				{
//					stream.write((char*)&it->first, sizeof(it->first));	//	vertex index
//					size = it->second.size();	//	count of bones effect this vertex
//					stream.write((char*)&size, sizeof(size));
//					for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
//					{
//						it2->first.Save(stream);	//	name of the bone
//						stream.write((char*)&it2->second, sizeof(it2->second));	//	weight
//					}
//				}
//			}
//		}

//		{
//			int count = m_tex_coords.size();
//			stream.write((char*)&count, sizeof(count));
//			if (count)
//			{
//				for (auto texture_set : m_tex_coords)
//				{
//					texture_set.first.Save(stream);	//	save name
//					int size = texture_set.second.size();	//	save textures
//					stream.write((char*)&size, sizeof(size));
//					if (size)
//					{
//						stream.write((char*)&texture_set.second[0], sizeof(texture_set.second[0]));
//					}
//				}
//			}
//		}

//		return true;
//	}

	
//	bool MeshDesc::Load(std::istream& stream)
//	{
//		{
//			int size override;
//			stream.read((char*)&size, sizeof(size));
//			if (size)
//			{
//				m_vertices.resize(size);
//				stream.read((char*)&m_vertices[0][0], sizeof(m_vertices[0][0])*size);
//			}
//		}

//		{
//			int size override;
//			stream.read((char*)&size, sizeof(size));
//			if (size)
//			{
//				m_normals.resize(size);
//				stream.read((char*)&m_normals[0][0], sizeof(m_normals[0][0])*size);
//			}
//		}

//		{
//			int size override;
//			stream.read((char*)&size, sizeof(size));
//			if (size)
//			{
//				m_faces.resize(size);
//				stream.read((char*)&m_faces[0][0], sizeof(m_faces[0][0])*size);
//			}
//		}

//		{
//			int size override;
//			stream.read((char*)&size, sizeof(size));
//			if (size)
//			{
//				for (int i = 0; i < size; ++i)
//				{
//					Virtual::VertexIndex index;
//					stream.read((char*)&index, sizeof(index));
//					std::map<System::string, float> weight;
//					int bone_count;
//					stream.read((char*)&bone_count, sizeof(bone_count));
//					for (int j = 0; j < bone_count; ++j)
//					{
//						System::string bone_name;
//						bone_name.Load(stream);
//						float weight;
//						stream.read((char*)&weight, sizeof(weight));	//	weight
//					}
//				}
//			}

//		}

//		{
//			int count= 0;
//			stream.read((char*)&count, sizeof(count));
//			if (count)
//			{
//				for (int i = 0; i < count; ++i)
//				{
//					System::string name;
//					name.Load(stream);
//					int size override;
//					stream.read((char*)&size, sizeof(size));
//					if (size)
//					{
//						m_tex_coords[name].resize(size);
//						stream.read((char*)&m_tex_coords[name][0][0], sizeof(m_tex_coords[name][0][0]));
//					}
//				}
//			}
//		}
//		return true;
//	}
//}
