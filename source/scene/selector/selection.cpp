#include "selection.h"

namespace Scene
{
    Selection::Selection()
        : m_object(nullptr)
    {
    }

    void Selection::SetPoints(const std::vector<Math::vec3> &value)
    {
        m_points = value;
    }

    void Selection::SetObject(System::Object* value)
    {
        m_object = value;
    }

    const std::vector<Math::vec3>& Selection::GetPoints() const
    {
        return m_points;
    }

    void Selection::SetFaces(const std::vector<size_t> &value)
    {
        m_faces = value;
    }

    const std::vector<size_t>& Selection::GetFaces() const
    {
        return m_faces;
    }

    System::Object* Selection::GetObject() const
    {
        return m_object;
    }

    void Selection::SetType(SelectionType value)
    {
        m_type = value;
    }

    SelectionType Selection::GetType() const
    {
        return m_type;
    }
}
