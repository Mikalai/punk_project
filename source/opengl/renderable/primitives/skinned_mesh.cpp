#include "..\..\gl\gl3.h"

#include "../../../system/logger.h"
#include "../../../math/helper.h"
#include "../../../utility/descriptors/mesh_desc.h"
#include "../../../utility/descriptors/armature_desc.h"
#include "../../../utility/descriptors/bone_desc.h"

#include "skinned_mesh.h"
#include "primitive_types.h"

namespace OpenGL
{
	SkinnedMesh::SkinnedMesh()
	{
		m_primitive_type = PrimitiveTypes::SKINNED_MESH;
	}

	System::Proxy<SkinnedMesh> SkinnedMesh::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios_base::binary);
		if (!stream.is_open())
			return (out_error() << "Can't load skinned mesh from " << path << std::endl, System::Proxy<SkinnedMesh>(nullptr));
		System::Proxy<SkinnedMesh> mesh(new SkinnedMesh);
		mesh->Load(stream);
		return mesh;
	}

	System::Proxy<SkinnedMesh> SkinnedMesh::CreateFromStream(std::istream& stream)
	{
		System::Proxy<SkinnedMesh> mesh(new SkinnedMesh);
		mesh->Load(stream);
		return mesh;
	}

	bool SkinnedMesh::Cook(const Utility::MeshDesc* mesh, const Utility::ArmatureDesc* armature)
	{				
		SetType(System::ObjectType::SKINNED_MESH);
		if (!mesh)
			return (out_error() << "Can't created skinned mesh from NULL mesh descriptor" << std::endl, false);
		if (mesh->m_vertices.empty())
			return (out_error() << "Can't create skinned mesh from empty vertex list in mesh descriptor" << std::endl, false);
		if (mesh->m_tex_coords.empty())
			return (out_error() << "Can't create skinned mesh from mesh descriptor with empty texture coordinates list" << std::endl, false);
		if (mesh->m_normals.empty())
			return (out_error() << "Can't create skinned mesh from mesh descriptor with empty normals list" << std::endl, false);
		if (mesh->m_bone_weights.empty())
			return (out_error() << "Can't create skinned mesh from mesh descriptor with empty bones weights list" << std::endl, false);
		
		std::vector<unsigned> ib(mesh->m_faces.size()*3);
		for (unsigned i = 0; i < mesh->m_faces.size()*3; i++)
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

			//	for each vertex in the triangle
			for (int j = 0; j < 3; ++j)
			{
				int index_0 = j;
				int index_1 = (j+1)%3;
				int index_2 = (j+2)%3;
					
				Math::CalculateTBN(position[index_0], position[index_1], position[index_2], texture[index_0], texture[index_1], texture[index_2], tgn, btn, nrm, det); 
				det = (det < 0) ? -1.0f : 1.0f;

				vb[index].m_position = position[index_0];
				vb[index].m_normal = normal[index_0];
				vb[index].m_texture0.Set(texture[index_0][0], texture[index_0][1], 0, 0);
				vb[index].m_tangent.Set(tgn[0], tgn[1], tgn[2], det);
				vb[index].m_bitangent.Set(btn[0], btn[1], btn[2], 0);

				if (!CookOneVertexWithBone(mesh, armature, f[j], vb[index].m_bones_id, vb[index].m_bone_weights))
					return (out_error() << "Can't cook skinned mesh, because error occured in cooking skinned vertex" << std::endl, false);

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
					v->m_normal = norm;
					v->m_tangent.Set(tang[0], tang[1], tang[2], w);
					v->m_bitangent = btan;
				}				
			}
		}
		SetVertexBuffer(vb);
		SetIndexBuffer(ib);

		return true;
	}

	bool SkinnedMesh::CookOneVertexWithBone(const Utility::MeshDesc* mesh, const Utility::ArmatureDesc* armature, int index, Math::Vector4<float>& bone, Math::Vector4<float>& weight) const
	{
		try
		{
			const Virtual::BoneWeights& weights = mesh->m_bone_weights.at(index);

			int b_id[4] = {0, 0, 0, 0};
			float w[4] = {0, 0, 0, 0};

			int used = 0;
			for (int i = 0, max_i = armature->m_bones.size(); i < max_i; ++i)
			{
				const Utility::BoneDesc* cur_bone = armature->m_bones[i];
				if (weights.find(cur_bone->m_name) != weights.end())
				{	
					// replace the least significant bone
					int Min = 0;
					for (int j = 0; j < 4; j++)
					{
						if (w[j] < w[Min])
							Min = j;
					}
					b_id[Min] = i;
					w[Min] = weights.at(cur_bone->m_name);
					used++;
				}
			}

			//	normalize
			float l = w[0] + w[1] + w[2] + w[3];

			if (l == 0)
				return (out_error() << "Can't cook skinned vertex because it has no bones assigned. Modify source model" << std::endl, false);

			if (w[0] < 0 || w[1] < 0 || w[2] < 0 || w[3] < 0)
				return (out_error() << "One of the bone weights is less than 0. It is incorrect" << std::endl, false);

			w[0] /= l; w[1] /= l; w[2] /= l; w[3] /= l;
			weight.Set(w[0], w[1], w[2], 1.0f - w[0] - w[1] - w[2]);
			bone.Set((float)b_id[0], (float)b_id[1], (float)b_id[2], (float)b_id[3]);
		}
		catch(std::out_of_range&)
		{
			out_error() << "Can't cook skinned vertex " << index << std::endl;
			return false;
		}
		return true;
	}

	bool SkinnedMesh::Save(std::ostream& stream) const
	{
		return VertexArrayObject2<PrimitiveType, VertexType>::Save(stream);
	}

	bool SkinnedMesh::Load(std::istream& stream)
	{
		return VertexArrayObject2<PrimitiveType, VertexType>::Load(stream);
	}
}