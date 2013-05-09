#ifdef USE_HUMANS

#ifndef HUMANSTATECLASS_H
#define HUMANSTATECLASS_H

#include "../era.h"

namespace Humans
{

class HumanState;

class HumanStateClass : public EntityClass
{
public:

    HumanStateClass(const std::string& name = "HumanStateClass");

    virtual void Register(Entity* value) override;
    virtual void Unregister(Entity* value) override;
    virtual void Destroy(Entity* value) override;

private:
    std::vector<HumanState*> m_all_human_states;
};

}

#endif // HUMANSTATECLASS_H

#endif  //  USE_HUMANS
