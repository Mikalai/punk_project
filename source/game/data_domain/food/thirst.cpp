#ifdef USE_FOOD

#include "thirst.h"

namespace Food
{

Thirst::Thirst()
    : m_current_level(0)
{
}

double Thirst::GetCurrentLevel() const
{
    return m_current_level;
}

void Thirst::Modify(double delta)
{
    m_current_level += delta;
}

}

#endif  //  USE_FOOD
