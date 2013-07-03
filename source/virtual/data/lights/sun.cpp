#include "sun.h"

namespace Virtual
{
    Sun::Sun()
    {
    }

    Sun::~Sun()
    {}

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
}
