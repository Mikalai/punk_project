#include "weight.h"
#include "weightclass.h"

namespace Common
{

Weight::Weight(double value)
    : m_value(value)
{}

void Weight::Set(double value)
{
    m_value = value;
}

double Weight::Get() const
{
    return m_value;
}

}
