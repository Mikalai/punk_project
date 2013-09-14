#include <math.h>
#include <limits>
#include "recount.h"

namespace Math
{
    const vec3 Recount::SphericalToCartesian(float phi, float theta)
    {
        float x = sin(theta)*cos(phi);
        float y = sin(theta)*sin(phi);
        float z = cos(theta);
        return vec3(x, y, z);
    }

    const vec3 Recount::SphericalToCartesian(float phi, float theta, float r)
    {
        float x = r*sin(theta)*cos(phi);
        float y = r*sin(theta)*sin(phi);
        float z = r*cos(theta);
        return vec3(x, y, z);
    }

    const vec3 Recount::SphericalToCartesian(const SphericalCoordinate& p)
    {
        float x = sin(p.Theta())*cos(p.Phi());
        float y = sin(p.Theta())*sin(p.Phi());
        float z = cos(p.Theta());
        return vec3(x, y, z);
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
