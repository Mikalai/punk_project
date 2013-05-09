#ifndef HUMANSTATE_H
#define HUMANSTATE_H

#include "../era.h"

namespace Humans
{

class HumanStateClass;

class HumanState : public Entity
{
public:

private:
    int m_age;
    std::string m_name;
    bool m_is_alive;

    int m_strength;
    int m_intelligence;

protected:
    HumanState(HumanStateClass* c);

    friend class HumanStateClass;
};

}

#endif // HUMANSTATE_H
