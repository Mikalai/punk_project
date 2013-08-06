#include "../../../math/helper.h"
#include "../../../virtual/skinning/module.h"
#include "../../../virtual/data/module.h"

#include "skin_mesh.h"

#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif	//	USE_OPENGL


namespace Gpu
{
#ifdef USE_OPENGL
    using SkinMeshBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES,
    Vertex<VertexComponent::Position,
    VertexComponent::Normal,
    VertexComponent::Tangent,
    VertexComponent::Bitangent,
    VertexComponent::Texture0,
    VertexComponent::BoneID,
    VertexComponent::BoneWeight>>;
#else
#endif

    bool CookOneVertexWithBone(const Virtual::SkinGeometry* mesh, const Virtual::Armature* armature, int index, Math::vec4& bone, Math::vec4& weight);

    class SkinMesh::SkinMeshImpl : public SkinMeshBase
    {
        using Base = SkinMeshBase;

    public:
        SkinMeshImpl(VideoDriver* driver) : Base(driver) {}

        bool Cook(const Virtual::SkinGeometry* mesh, const Virtual::Armature* armature)
        {
            if (!mesh)
                throw System::PunkInvalidArgumentException(L"Can't created skinned mesh from NULL mesh descriptor");
            if (mesh->GetVertices().empty())
                throw System::PunkInvalidArgumentException(L"Can't create skinned mesh from empty vertex list in mesh descriptor");
            if (mesh->GetTextureMeshes().empty())
                throw System::PunkInvalidArgumentException(L"Can't create skinned mesh from mesh descriptor with empty texture coordinates list");
            if (mesh->GetNormals().empty())
                throw System::PunkInvalidArgumentException(L"Can't create skinned mesh from mesh descriptor with empty normals list");
            if (mesh->GetBoneWeights().empty())
                throw System::PunkInvalidArgumentException(L"Can't create skinned mesh from mesh descriptor with empty bones weights list");

            std::vector<unsigned> ib(mesh->GetFaces().size()*3);

            for (unsigned i = 0; i < ib.size(); i++)
                ib[i] = i;

            std::vector<CurrentVertex> vb(mesh->GetFaces().size()*3);

            std::vector<int> base_index;		/// contains vertex index in the source array
            int index = 0;
            for (unsigned i = 0, max_i = mesh->GetTextureMeshes().begin()->second.size(); i < max_i; i++)
            {
                const Math::ivec3& f = mesh->GetFaces()[i];
                const Math::vec3 position[3] = { mesh->GetVertices()[f[0]], mesh->GetVertices()[f[1]], mesh->GetVertices()[f[2]] };
                const Math::vec2 texture[3] = { mesh->GetTextureMeshes().begin()->second[i][0], mesh->GetTextureMeshes().begin()->second[i][1], mesh->GetTextureMeshes().begin()->second[i][2] };
                const Math::vec3 normal[3] = { mesh->GetNormals()[f[0]], mesh->GetNormals()[f[1]], mesh->GetNormals()[f[2]] };

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
                    CurrentVertex* v = &vb[j];
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
                    CurrentVertex* v = &vb[j];
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

            Base::Cook();
            return true;
        }
    };

	bool CookOneVertexWithBone(const Virtual::SkinGeometry* mesh, const Virtual::Armature* armature, int index, Math::vec4& bone, Math::vec4& weight)
	{
		const Virtual::BoneWeights& weights = mesh->GetBoneWeights().at(index);

		int b_id[4] = {0, 0, 0, 0};
		float w[4] = {0, 0, 0, 0};

        int used = 0;
		for (int i = 0, max_i = armature->GetBonesCount(); i < max_i; ++i)
		{
			const Virtual::Bone* cur_bone = armature->GetBoneByIndex(i);
			if (weights.find(cur_bone->GetName()) != weights.end())
			{
				// replace the least significant bone
                int Min = 0;
				for (int j = 0; j < 4; j++)
				{
					if (w[j] < w[Min])
						Min = j;
				}
				b_id[Min] = i;
				w[Min] = weights.at(cur_bone->GetName());
				used++;
			}
		}

		//	normalize
		float l = w[0] + w[1] + w[2] + w[3];

		if (l == 0)
			throw System::PunkInvalidArgumentException(L"Can't cook skinned vertex because it has no bones assigned. Modify source model");

		if (w[0] < 0 || w[1] < 0 || w[2] < 0 || w[3] < 0)
			throw System::PunkInvalidArgumentException(L"One of the bone weights is less than 0. It is incorrect");

		w[0] /= l; w[1] /= l; w[2] /= l; w[3] /= l;
		weight.Set(w[0], w[1], w[2], 1.0f - w[0] - w[1] - w[2]);
		bone.Set((float)b_id[0], (float)b_id[1], (float)b_id[2], (float)b_id[3]);
		return true;
	}

    SkinMesh::SkinMesh(VideoDriver* driver)
        : impl(new SkinMeshImpl(driver))
    {}

    SkinMesh::~SkinMesh()
    {
        delete impl;
        impl = nullptr;
    }

    bool SkinMesh::Cook(const Virtual::SkinGeometry* mesh, const Virtual::Armature* armature)
    {
        impl->Cook(mesh, armature);
    }

    void SkinMesh::Bind(int64_t value)
    {
        impl->Bind(value);
    }

    void SkinMesh::Unbind()
    {
        impl->Unbind();
    }

    void SkinMesh::Render()
    {
        impl->Render();
    }

    bool SkinMesh::HasData()
    {
        return impl->HasData();
    }
}
