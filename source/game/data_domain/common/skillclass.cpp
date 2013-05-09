#include <algorithm>
#include "skillclass.h"
#include "skill.h"

namespace Common
{

std::vector<Entity*> SkillClass::m_all_skills;

SkillClass::SkillClass(const std::string& name)
    : EntityClass(name)
{
}

void SkillClass::Destroy(Entity *value)
{
    Unregister(value);
    delete value;
}

void SkillClass::Register(Entity *value)
{
    m_all_skills.push_back(dynamic_cast<Skill*>(value));
    EntityClass::Register(value);
}

void SkillClass::Unregister(Entity *value)
{
    auto it = std::find(m_all_skills.begin(), m_all_skills.end(), dynamic_cast<Skill*>(value));
    if (it == m_all_skills.end())
        return;
    m_all_skills.erase(it);

    EntityClass::Unregister(value);
}

}
