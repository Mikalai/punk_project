#ifndef SKILL_H
#define SKILL_H

#include <map>
#include "../era.h"

namespace Common
{

class SkillClass;

class Skill : public Entity
{
public:
    Skill(SkillClass* c);
};

void AcquireSkill(Entity* h, Skill* s);
void LooseSkill(Entity* h, Skill* s);
const std::map<const std::string, Skill*> FindAllSkills(Entity* h);

}

#endif // SKILL_H
