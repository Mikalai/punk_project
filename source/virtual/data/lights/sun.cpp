#include "sun.h"
#include "../../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(Sun, "Virtual.Sun", PUNK_SUN, &System::Object::Info.Type);

    Sun::Sun()
    {
        Info.Add(this);
    }

    Sun::~Sun()
    {
        Info.Remove(this);
    }

    void Sun::SetEnergy(float value)
    {
        m_energy = value;
    }

    float Sun::GetEnergy() const
    {
        return m_energy;
    }

    void Sun::SetColor(const Math::vec3& value)
    {
        m_color = value;
    }

    const Math::vec3& Sun::GetColor() const
    {
        return m_color;
    }

    void Sun::SetName(const System::string& value)
    {
        m_name = value;
    }

    const System::string& Sun::GetName() const
    {
        return m_name;
    }

}
