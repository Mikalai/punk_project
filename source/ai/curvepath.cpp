#include "curvepath.h"
#include "../engine_objects.h"

namespace AI
{
    PUNK_OBJECT_REG(CurvePath, "AI.CurvePath", PUNK_CURVE_PATH, &System::Object::Info.Type);

    CurvePath::CurvePath()
    {
        Info.Add(this);
    }

    CurvePath::~CurvePath()
    {
        Info.Remove(this);
    }

    void CurvePath::SetName(const System::string& value)
    {
        m_name = value;
    }

    const System::string& CurvePath::GetName() const
    {
        return m_name;
    }
}
