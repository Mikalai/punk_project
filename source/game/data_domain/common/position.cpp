#include "position.h"

namespace Common
{

Location::Location()
{
}

void Location::SetPosition(const Math::vec3 &value)
{
    m_position = value;
}

const Math::vec3& Location::GetPosition() const
{
    return m_position;
}

bool HasLocation(Entity *value)
{
    auto location = GetAttribute<Location>(value);
    return location != nullptr;
}

}
