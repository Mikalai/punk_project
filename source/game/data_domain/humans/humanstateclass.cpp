#ifdef USE_HUMANS

#include <algorithm>
#include "humanstateclass.h"
#include "humanstate.h"

namespace Humans
{

HumanStateClass::HumanStateClass(const std::string& value)
    : EntityClass(value)
{
}

void HumanStateClass::Destroy(Entity *value)
{
    Unregister(value);
    delete value;
}

void HumanStateClass::Register(Entity *value)
{
    m_all_human_states.push_back(dynamic_cast<HumanState*>(value));
    EntityClass::Register(value);
}

void HumanStateClass::Unregister(Entity *value)
{
    auto it = std::find(m_all_human_states.begin(), m_all_human_states.end(), dynamic_cast<HumanState*>(value));
    if (it == m_all_human_states.end())
        return;
    m_all_human_states.erase(it);

    EntityClass::Unregister(value);
}

}

#endif  //  USE_HUMANS
