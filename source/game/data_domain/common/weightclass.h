#ifndef WEIGHTCLASS_H
#define WEIGHTCLASS_H

#include "../era.h"

namespace Common
{

class Weight;

class WeightClass : public EntityClass
{
public:

    WeightClass(const std::string& name);

    Weight* Create();

private:
    static std::vector<Weight*> m_all_weights;
};

}

#endif // WEIGHTCLASS_H
