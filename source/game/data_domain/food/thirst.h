#ifdef USE_FOOD

#ifndef THIRST_H
#define THIRST_H

#include "../era.h"

namespace Food
{

class Thirst : public Attribute
{
public:
    Thirst();

    double GetCurrentLevel() const;

    void Modify(double delta);

private:

    double m_current_level;

    static constexpr double MAX_VALUE = 100.0;
};

}

#endif // THIRST_H

#endif  //  USE_FOOD
