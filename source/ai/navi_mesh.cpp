#include "navi_mesh.h"

namespace AI
{
    NaviMesh::NaviMesh()
    {}

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
}
