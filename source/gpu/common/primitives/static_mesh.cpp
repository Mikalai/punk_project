#include <vector>
#include <fstream>

#include "../../../math/helper.h"
#include "../../../virtual/data/static_geometry.h"

#include "static_mesh.h"

#ifdef USE_OPENGL
#include "../../opengl/renderable/module.h"
#else
#endif	//	USE_OPENGL


namespace Gpu
{
#ifdef USE_OPENGL
    using StaticMeshPositionNormalTangentBitangentTexture0Base = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES,
    Vertex<VertexComponent::Position,
    VertexComponent::Normal,
    VertexComponent::Tangent,
    VertexComponent::Bitangent,
    VertexComponent::Texture0>>;

    using StaticMeshPositionNormalBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES,
    Vertex<VertexComponent::Position,
    VertexComponent::Normal>>;

    using StaticMeshPositionBase = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES,
    Vertex<VertexComponent::Position>>;

    using StaticMeshPositionTexture0Base = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES,
    Vertex<VertexComponent::Position,
    VertexComponent::Texture0>>;

    using StaticMeshPositionNormalTexture0Base = OpenGL::VertexArrayObject2<PrimitiveType::TRIANGLES,
    Vertex<VertexComponent::Position,
    VertexComponent::Normal,
    VertexComponent::Texture0>>;
#else
#endif

    class StaticMeshPositionNormalTangentBitangentTexture0 : public StaticMeshPositionNormalTangentBitangentTexture0Base
    {
        using Base = StaticMeshPositionNormalTangentBitangentTexture0Base;

    public:

        StaticMeshPositionNormalTangentBitangentTexture0(VideoDriver* driver) : Base(driver) {}

        bool Cook(Virtual::StaticGeometry* mesh)
        {
            if (mesh->GetVertices().empty())
                throw System::PunkInvalidArgumentException(L"Can't create static mesh from empty vertex list in mesh descriptor");
            if (mesh->GetTextureMeshes().empty())
                throw System::PunkInvalidArgumentException(L"Can't create static mesh from mesh descriptor with empty texture coordinates list");
            if (mesh->GetNormals().empty())
                throw System::PunkInvalidArgumentException(L"Can't create static mesh from mesh descriptor with empty normals list");

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

            Base::SetVertexBuffer(vb);
            Base::SetIndexBuffer(ib);
            Base::Cook();

            return true;
        }
    };

    class StaticMeshPositionNormal : public StaticMeshPositionNormalBase
    {
        using Base = StaticMeshPositionNormalBase;

    public:

        StaticMeshPositionNormal(VideoDriver* driver) : Base(driver) {}

        bool Cook(Virtual::StaticGeometry* mesh)
        {
            if (mesh->GetVertices().empty())
                throw System::PunkInvalidArgumentException(L"Can't create static mesh from empty vertex list in mesh descriptor");
            if (mesh->GetNormals().empty())
                throw System::PunkInvalidArgumentException(L"Can't create static mesh from mesh descriptor with empty normals list");

            std::vector<unsigned> ib(mesh->GetFaces().size()*3);

            for (unsigned i = 0; i < ib.size(); i++)
                ib[i] = i;

            std::vector<CurrentVertex> vb(mesh->GetFaces().size()*3);

            std::vector<int> base_index;		/// contains vertex index in the source array
            int index = 0;
            for (unsigned i = 0, max_i = mesh->GetFaces().size(); i < max_i; i++)
            {
                const Math::ivec3& f = mesh->GetFaces()[i];
                const Math::vec3 position[3] = { mesh->GetVertices()[f[0]], mesh->GetVertices()[f[1]], mesh->GetVertices()[f[2]] };
                const Math::vec3 normal[3] = { mesh->GetNormals()[f[0]], mesh->GetNormals()[f[1]], mesh->GetNormals()[f[2]] };

                for (int j = 0; j < 3; ++j)
                {
                    vb[index].m_position = position[j];
                    vb[index].m_normal = normal[j];
                    base_index.push_back(f[j]);
                    index++;
                }
            }

            /// Smooth TBN
            std::vector<int> mask(vb.size());
            for (int i = 0; i < (int)vb.size(); i++)
            {
                Math::vec3 norm;
                for (int j = 0; j < (int)vb.size(); j++)
                {
                    CurrentVertex* v = &vb[j];
                    if (base_index[j] == i)
                    {
                        norm += v->m_normal.XYZ();
                    }
                }

                norm.Normalize();

                for (int j = 0; j < (int)vb.size(); j++)
                {
                    CurrentVertex* v = &vb[j];
                    if (base_index[j] == i)
                    {
                        v->m_normal = norm;
                    }
                }
            }

            Base::SetVertexBuffer(vb);
            Base::SetIndexBuffer(ib);
            Base::Cook();

            return true;
        }
    };

    class StaticMeshPosition : public StaticMeshPositionBase
    {
        using Base = StaticMeshPositionBase;

    public:

        StaticMeshPosition(VideoDriver* driver) : Base(driver) {}

        bool Cook(Virtual::StaticGeometry* mesh)
        {
            if (mesh->GetVertices().empty())
                throw System::PunkInvalidArgumentException(L"Can't create static mesh from empty vertex list in mesh descriptor");

            std::vector<unsigned> ib(mesh->GetFaces().size()*3);

            for (unsigned i = 0; i < ib.size(); i++)
                ib[i] = i;

            std::vector<CurrentVertex> vb(mesh->GetFaces().size()*3);

            std::vector<int> base_index;		/// contains vertex index in the source array
            int index = 0;
            for (unsigned i = 0, max_i = mesh->GetFaces().size(); i < max_i; i++)
            {
                const Math::ivec3& f = mesh->GetFaces()[i];
                const Math::vec3 position[3] = { mesh->GetVertices()[f[0]], mesh->GetVertices()[f[1]], mesh->GetVertices()[f[2]] };

                for (int j = 0; j < 3; ++j)
                {
                    vb[index].m_position = position[j];
                    base_index.push_back(f[j]);
                    index++;
                }
            }

            Base::SetVertexBuffer(vb);
            Base::SetIndexBuffer(ib);
            Base::Cook();

            return true;
        }
    };

    class StaticMeshPositionTexture0 : public StaticMeshPositionTexture0Base
    {
        using Base = StaticMeshPositionTexture0Base;

    public:

        StaticMeshPositionTexture0(VideoDriver* driver) : Base(driver) {}

        bool Cook(Virtual::StaticGeometry* mesh)
        {
            if (mesh->GetVertices().empty())
                throw System::PunkInvalidArgumentException(L"Can't create static mesh from empty vertex list in mesh descriptor");
            if (mesh->GetTextureMeshes().empty())
                throw System::PunkInvalidArgumentException(L"Can't create static mesh from mesh descriptor with empty texture coordinates list");

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

                for (int j = 0; j < 3; ++j)
                {
                    vb[index].m_position = position[j];
                    vb[index].m_texture0.Set(texture[j][0], texture[j][1], 0, 0);
                    base_index.push_back(f[j]);
                    index++;
                }
            }

            Base::SetVertexBuffer(vb);
            Base::SetIndexBuffer(ib);
            Base::Cook();

            return true;
        }
    };

    class StaticMeshPositionNormalTexture0 : public StaticMeshPositionNormalTexture0Base
    {
        using Base = StaticMeshPositionNormalTexture0Base;

    public:

        StaticMeshPositionNormalTexture0(VideoDriver* driver) : Base(driver) {}

        bool Cook(Virtual::StaticGeometry* mesh)
        {
            if (mesh->GetVertices().empty())
                throw System::PunkInvalidArgumentException(L"Can't create static mesh from empty vertex list in mesh descriptor");
            if (mesh->GetTextureMeshes().empty())
                throw System::PunkInvalidArgumentException(L"Can't create static mesh from mesh descriptor with empty texture coordinates list");
            if (mesh->GetNormals().empty())
                throw System::PunkInvalidArgumentException(L"Can't create static mesh from mesh descriptor with empty normals list");

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

                for (int j = 0; j < 3; ++j)
                {
                    vb[index].m_position = position[j];
                    vb[index].m_normal = normal[j];
                    vb[index].m_texture0.Set(texture[j][0], texture[j][1], 0, 0);
                    base_index.push_back(f[j]);
                    index++;
                }
            }

            /// Smooth TBN
            std::vector<int> mask(vb.size());
            for (int i = 0; i < (int)vb.size(); i++)
            {
                Math::vec3 norm;
                for (int j = 0; j < (int)vb.size(); j++)
                {
                    CurrentVertex* v = &vb[j];
                    if (base_index[j] == i)
                    {
                        norm += v->m_normal.XYZ();
                    }
                }

                norm.Normalize();

                for (int j = 0; j < (int)vb.size(); j++)
                {
                    CurrentVertex* v = &vb[j];
                    if (base_index[j] == i)
                    {
                        v->m_normal = norm;
                    }
                }
            }

            Base::SetVertexBuffer(vb);
            Base::SetIndexBuffer(ib);
            Base::Cook();

            return true;
        }
    };
    StaticMesh::StaticMesh(VideoDriver *driver)
        : impl(nullptr)
        , m_driver(driver)
	{}

    StaticMesh::~StaticMesh()
    {
        delete impl;
        impl = nullptr;
    }

	bool StaticMesh::Cook(Virtual::StaticGeometry* mesh)
	{
        if (!mesh->GetVertices().empty() && !mesh->GetTextureMeshes().empty() && mesh->GetNormals().empty())
        {
            delete impl;
            auto p = new StaticMeshPositionNormalTangentBitangentTexture0(m_driver);
            impl = p;
            p->Cook(mesh);
            return true;
        }
        else if (!mesh->GetVertices().empty() && !mesh->GetTextureMeshes().empty())
        {
            delete impl;
            auto p = new StaticMeshPositionTexture0(m_driver);
            p->Cook(mesh);
            impl = p;
            return true;
        }
        else if (!mesh->GetVertices().empty() && !mesh->GetNormals().empty())
        {
            delete impl;
            auto p = new StaticMeshPositionNormal(m_driver);
            p->Cook(mesh);
            impl = p;
            return true;
        }
        else if (!mesh->GetVertices().empty())
        {
            delete impl;
            auto p = new StaticMeshPosition(m_driver);
            p->Cook(mesh);
            impl = p;
            return true;
        }
        return false;
	}

    void StaticMesh::Bind(int64_t value)
    {
        impl->Bind(value);
    }

    void StaticMesh::Unbind()
    {
        impl->Unbind();
    }

    void StaticMesh::Render()
    {
        impl->Render();
    }

    bool StaticMesh::HasData()
    {
        return impl->HasData();
    }
}
