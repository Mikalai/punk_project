#include "hunger.h"

namespace Food
{

Hunger::Hunger()
    : m_current_level(0)
{
}

void Hunger::Modify(double delta)
{
    m_current_level += delta;
}

double Hunger::GetCurrentLevel() const
{
    return m_current_level;
}

}
