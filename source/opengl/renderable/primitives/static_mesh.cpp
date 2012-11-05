#include "..\..\gl\gl3.h"
#include <vector>
#include <fstream>

#include "../../../system/logger.h"
#include "../../../math/helper.h"
#include "../../../utility/descriptors/mesh_desc.h"

#include "static_mesh.h"


namespace OpenGL
{

	StaticMesh* StaticMesh::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios_base::binary);
		if (!stream.is_open())
			return (out_error() << "Can't load static mesh from " << path << std::endl, nullptr);
		std::unique_ptr<StaticMesh> mesh(new StaticMesh);
		mesh->Load(stream);
		return mesh.release();
	}

	StaticMesh* StaticMesh::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<StaticMesh> mesh(new StaticMesh);
		mesh->Load(stream);
		return mesh.release();
	}

	bool StaticMesh::Save(std::ostream& stream)
	{
		return VertexArrayObject2<PrimitiveType, VertexType>::Save(stream);
	}

	bool StaticMesh::Load(std::istream& stream)
	{
		return VertexArrayObject2<PrimitiveType, VertexType>::Load(stream);
	}

	bool StaticMesh::Cook(Utility::MeshDesc* mesh)
	{				
		SetType(System::PERMANENT_RESOURCE_STATIC_MESH);
		if (mesh->m_vertices.empty())
			return (out_error() << "Can't create static mesh from empty vertex list in mesh descriptor" << std::endl, false);
		if (mesh->m_tex_coords.empty())
			return (out_error() << "Can't create static mesh from mesh descriptor with empty texture coordinates list" << std::endl, false);
		if (mesh->m_normals.empty())
			return (out_error() << "Can't create static mesh from mesh descriptor with empty normals list" << std::endl, false);

		std::vector<unsigned> ib(mesh->m_faces.size()*3);

		for (unsigned i = 0; i < ib.size(); i++)
			ib[i] = i;

		std::vector<Utility::Vertex<VertexType>> vb(mesh->m_faces.size()*3);			

		std::vector<int> base_index;		/// contains vertex index in the source array
		int index = 0;
		for (unsigned i = 0, max_i = mesh->m_tex_coords.begin()->second.size(); i < max_i; i++)
		{
			const Math::ivec3& f = mesh->m_faces[i];
			const Math::vec3 position[3] = { mesh->m_vertices[f[0]], mesh->m_vertices[f[1]], mesh->m_vertices[f[2]] };
			const Math::vec2 texture[3] = { mesh->m_tex_coords.begin()->second[i][0], mesh->m_tex_coords.begin()->second[i][1], mesh->m_tex_coords.begin()->second[i][2] };
			const Math::vec3 normal[3] = { mesh->m_normals[f[0]], mesh->m_normals[f[1]], mesh->m_normals[f[2]] };

			Math::vec3 tgn;
			Math::vec3 nrm;
			Math::vec3 btn;
			float det;

			for (int j = 0; j < 3; ++j) 
			{
				int index_0 = j;
				int index_1 = (j+1)%3;
				int index_2 = (j+2)%3;
					
				Math::CalculateTBN(position[index_0], position[index_1], position[index_2], texture[index_0], texture[index_1], texture[index_2], tgn, btn, nrm, det); 

				det = (det < 0) ? -1.0f : 1.0f;

				vb[index].m_position = position[index_0].ToHomogeneous();
				vb[index].m_normal = normal[index_0].ToHomogeneous();
				vb[index].m_texture0.Set(texture[index_0][0], texture[index_0][1], 0, 0);
				vb[index].m_tangent.Set(tgn[0], tgn[1], tgn[2], det);
				vb[index].m_bitangent.Set(btn[0], btn[1], btn[2], 0);
				base_index.push_back(f[j]);
				index++;
			}			
		}

		/// Smooth TBN
		std::vector<int> mask(vb.size());
		for (int i = 0; i < (int)vb.size(); i++)
		{
			Math::vec3 norm;
			Math::vec3 tang;
			Math::vec3 btan;
			for (int j = 0; j < (int)vb.size(); j++)
			{
				Utility::Vertex<VertexType>* v = &vb[j];
				if (base_index[j] == i)
				{					
					norm += v->m_normal.XYZ();
					tang += v->m_tangent.XYZ();
					btan += v->m_bitangent.XYZ();
				}				
			}

			norm.Normalize();
			tang.Normalize();
			btan.Normalize();
			tang = (tang - norm.Dot(tang)*norm).Normalized();
			btan = (btan - norm.Dot(btan)*norm - tang.Dot(btan)*tang).Normalized();

			Math::Matrix<float> m(3,3);
			m.At(0,0) = tang[0]; m.At(0,1) = tang[1]; m.At(0,2) = tang[2];
			m.At(1,0) = btan[0]; m.At(1,1) = btan[1]; m.At(1,2) = btan[2];
			m.At(2,0) = norm[0]; m.At(2,1) = norm[1]; m.At(2,2) = norm[2];
			float w = m.Determinant();

			for (int j = 0; j < (int)vb.size(); j++)
			{	
				Utility::Vertex<VertexType>* v = &vb[j];
				if (base_index[j] == i)
				{					
					v->m_normal = norm.ToHomogeneous();
					v->m_tangent.Set(tang[0], tang[1], tang[2], w);
					v->m_bitangent = btan.ToHomogeneous();
				}				
			}
		}
		SetVertexBuffer(vb);
		SetIndexBuffer(ib);
		
		return VertexArrayObject2<PrimitiveType, VertexType>::Cook();		
	}
}