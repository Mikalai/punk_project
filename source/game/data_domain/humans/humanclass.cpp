#ifdef USE_HUMANS

#include <algorithm>
#include "humanclass.h"
#include "human.h"

namespace Humans
{

std::vector<Human*> HumanClass::m_all_humans;

HumanClass::HumanClass(const std::string &name)
    : EntityClass(name)
{}

void HumanClass::Destroy(Entity *value)
{
    Unregister(value);
    delete value;
}

void HumanClass::Register(Entity *value)
{
    m_all_humans.push_back(dynamic_cast<Human*>(value));
    EntityClass::Register(value);
}

void HumanClass::Unregister(Entity *value)
{
    auto it = std::find(m_all_humans.begin(), m_all_humans.end(), dynamic_cast<Human*>(value));
    if (it == m_all_humans.end())
        return;
    m_all_humans.erase(it);

    EntityClass::Unregister(value);
}

std::vector<Human*>& HumanClass::AllHumans()
{
    return m_all_humans;
}

}

#endif  //   USE_HUMANS
