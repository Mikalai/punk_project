#ifndef HUNGER_H
#define HUNGER_H

#include "../era.h"

namespace Food
{

class Hunger : public Attribute
{
public:
    Hunger();

    double GetCurrentLevel() const;

    void Modify(double delta);

private:

    double m_current_level;

    static constexpr double MAX_VALUE = 100.0;
};

}

#endif // HUNGER_H
