#include <math.h>
#include <limits>
#include "recount.h"

namespace Math
{
    const vec3 Recount::SphericalToCartesian(float phi, float theta)
    {
        return SphericalToCartesian(phi, theta, 1);
    }

    const vec3 Recount::SphericalToCartesian(float phi, float theta, float r)
    {
        float x = r*cos(theta)*cos(phi);
        float y = r*cos(theta)*sin(phi);
        float z = r*sin(theta);
        return vec3(x, y, z);
    }

    const vec3 Recount::SphericalToCartesian(const SphericalCoordinate& p)
    {
        return SphericalToCartesian(p.Phi(), p.Theta(), p.R());
    }

    const SphericalCoordinate Recount::CartesianToSpherical(float x, float y, float z)
    {
        float r = sqrt(x*x + y*y + z*z);
        if (r < std::numeric_limits<float>::epsilon())
        {
            return SphericalCoordinate(0,0,0);
        }
        float theta = acos(z/r);
        float phi = atan2(y, x);
        return SphericalCoordinate(phi, theta, r);
    }

    const SphericalCoordinate Recount::CartesianToSpherical(const vec3& value)
    {
        return CartesianToSpherical(value[0], value[1], value[2]);
    }

    float Recount::DegToRad(float value)
    {
        return value / 180.0f * M_PI;
    }

    float Recount::RadToDeg(float value)
    {
        return value / M_PI * 180.0f;
    }
}
