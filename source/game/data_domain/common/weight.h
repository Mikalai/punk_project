#ifndef WEIGHT_H
#define WEIGHT_H

#include "../era.h"

namespace Common
{

class Weight : public Attribute
{
public:
    Weight(double value);
    void Set(double value);
    double Get() const;

private:
    double m_value;
};

}
#endif // WEIGHT_H
