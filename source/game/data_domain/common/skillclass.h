#ifndef SKILLCLASS_H
#define SKILLCLASS_H

#include "../era.h"

namespace Common
{

class SkillClass : public EntityClass
{
public:

    SkillClass(const std::string& name);

    virtual void Destroy(Entity* value) = 0;

    virtual void Register(Entity* e);
    virtual void Unregister(Entity* e);

private:
    static std::vector<Entity*> m_all_skills;

};

}

#endif // SKILLCLASS_H
