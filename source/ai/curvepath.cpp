#include "curvepath.h"
#include "../engine_objects.h"

namespace AI
{
    PUNK_OBJECT_REG(CurvePath, "AI.CurvePath", PUNK_CURVE_PATH, SaveCurvePath, LoadCurvePath, &System::Object::Info.Type);

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

    void SaveCurvePath(System::Buffer *buffer, const System::Object *o)
    {
        System::SaveObject(buffer, o);
        const CurvePath* p = Cast<const CurvePath*>(o);
        Math::SaveCurve(buffer, *p);
        System::SaveString(buffer, p->Name());
    }

    void LoadCurvePath(System::Buffer *buffer, System::Object *o)
    {
        System::LoadObject(buffer, o);
        CurvePath* p = Cast<CurvePath*>(o);
        Math::LoadCurve(buffer, *p);
        System::LoadString(buffer, p->m_name);
    }
}
