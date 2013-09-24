#include "navi_mesh.h"
#include "../system/buffer.h"
#include "../engine_objects.h"

namespace AI
{
    PUNK_OBJECT_REG(NaviMesh, "AI.NaviMesh", PUNK_NAVI_MESH, SaveNaviMesh, LoadNaviMesh, &System::Object::Info.Type);

    NaviMesh::NaviMesh()
    {
        Info.Add(this);
    }

    NaviMesh::~NaviMesh()
    {
        Info.Remove(this);
    }

    void NaviMesh::SetTransform(const Math::mat4& value)
    {
        m_transfrom = value;
    }

    const Math::mat4& NaviMesh::GetTranform() const
    {
        return m_transfrom;
    }

    NaviMesh* NaviMesh::CreateFromFile(const System::string& path)
    {
        return nullptr;
    }

    const Math::vec3& NaviMesh::GetPoint(int index) const
    {
        return m_points[index];
    }

    void NaviMesh::SetPoints(const Points &value)
    {
        m_points = value;
    }

    void NaviMesh::SetNormals(const Normals& value)
    {
        m_normals = value;
    }

    void NaviMesh::SetFaces(const Faces& value)
    {
        m_faces = value;
    }

    const NaviMesh::Points& NaviMesh::GetPoints() const
    {
        return m_points;
    }

    const NaviMesh::Faces& NaviMesh::GetFaces() const
    {
        return m_faces;
    }

    void NaviMesh::SetName(const System::string& value)
    {
        m_name = value;
    }

    const System::string& NaviMesh::GetName() const
    {
        return m_name;
    }

    void SaveNaviMesh(System::Buffer *buffer, const System::Object *o)
    {
        System::SaveObject(buffer, o);
        const NaviMesh* m = Cast<const NaviMesh*>(o);
        System::SaveString(buffer, m->m_name);
        Math::SaveMatrix4f(buffer, m->m_transfrom);
        unsigned size = m->m_points.size();
        buffer->WriteUnsigned32(size);
        for (auto& p : m->m_points)
        {
            Math::SaveVector3f(buffer, p);
        }

        size = m->m_normals.size();
        buffer->WriteUnsigned32(size);
        for (auto& p : m->m_normals)
        {
            Math::SaveVector3f(buffer, p);
        }

        size = m->m_points.size();
        buffer->WriteUnsigned32(size);
        for (auto& p : m->m_faces)
        {
            Math::SaveVector3i(buffer, p);
        }
    }

    void LoadNaviMesh(System::Buffer *buffer, System::Object *o)
    {
        System::LoadObject(buffer, o);
        NaviMesh* m = Cast<NaviMesh*>(o);
        System::LoadString(buffer, m->m_name);
        Math::LoadMatrix4f(buffer, m->m_transfrom);
        unsigned size = buffer->ReadUnsigned32();
        m->m_points.resize(size);
        for (auto& p : m->m_points)
        {
            Math::LoadVector3f(buffer, p);
        }

        size = buffer->ReadUnsigned32();
        m->m_normals.resize(size);
        for (auto& p : m->m_normals)
        {
            Math::LoadVector3f(buffer, p);
        }

        size = buffer->ReadUnsigned32();
        m->m_points.resize(size);
        for (auto& p : m->m_faces)
        {
            Math::LoadVector3i(buffer, p);
        }
    }
}
