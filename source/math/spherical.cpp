#include "spherical.h"

namespace Math
{
    SphericalCoordinate::SphericalCoordinate()
        : m_v{0,0,1}
    {}

    SphericalCoordinate::SphericalCoordinate(real phi, real theta)
        : m_v{phi, theta, 1}
    {}

    SphericalCoordinate::SphericalCoordinate(real phi, real theta, real r)
        : m_v{phi, theta, r}
    {}
}
