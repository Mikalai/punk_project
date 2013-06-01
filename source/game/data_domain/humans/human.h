#ifdef USE_HUMANS

#ifndef HUMAN_H
#define HUMAN_H

#include <map>
#include <string>
#include "../era.h"

namespace Humans
{

class HumanClass;

class Human : public Entity
{
public:
    virtual ~Human();

    void SetName(const std::string name) { m_name = name; }
    void SetAge(int age) { m_age = age; }

    const std::string GetName() const { return m_name; }
    int GetAge() const { return m_age; }

    void Die() { m_dead = true; }
    bool IsDead() const { return m_dead; }

private:

    std::string m_name;
    int m_age;
    bool m_alive;
    bool m_sleep;
    bool m_dead;

protected:
    Human(HumanClass* c);

};

}

#endif // HUMAN_H

#endif  //  USE_HUMANS
