#include <algorithm>
#include "entityclass.h"
#include "entity.h"

std::vector<Entity*> EntityClass::m_all_entities;

EntityClass::EntityClass(const std::string& name)
    : m_name(name)
{
}

void EntityClass::Register(Entity *e)
{
    m_all_entities.push_back(e);
}

void EntityClass::Unregister(Entity *e)
{
    auto it = std::find(m_all_entities.begin(), m_all_entities.end(), e);
    if (it == m_all_entities.end())
        return;
    m_all_entities.erase(it);
}
