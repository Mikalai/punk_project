#ifdef USE_HUMANS

#ifndef HUMANCLASS_H
#define HUMANCLASS_H

#include "../era.h"

namespace Humans
{

class Human;

class HumanClass : public EntityClass
{
public:

    HumanClass(const std::string& name = "HumanClass");

    virtual void Register(Entity* value) override;
    virtual void Unregister(Entity* value) override;
    virtual void Destroy(Entity* value) override;

    static std::vector<Human*>& AllHumans();

private:
    static std::vector<Human*> m_all_humans;
};

}

#endif // HUMANCLASS_H

#endif // USE_HUMANS
