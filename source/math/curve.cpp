#include "curve.h"

namespace Math
{
    Curve::Curve()
    {
    }

    void Curve::AddSpline(const Spline& value)
    {
        m_splines.push_back(value);
    }
}
