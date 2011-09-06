#ifndef LINE_H
#define LINE_H

#include "config.h"
#include "vec3.h"

namespace Math
{
	class LIB_MATH Plane;

    class LIB_MATH Line
    {
        vec3 origin;
        vec3 direction;
    public:       
        enum Location {LOCATION_ON, LOCATION_OUT, LOCATION_CROSS, LOCATION_PARALLEL, LOCATION_BELONG};

        Line();
        Line(vec3 org, vec3 dir);
        Location Classify(const vec3& Point) const;
        vec3 PointAt(float t) const;
        Location Classify(const Plane& p) const;

    };
}
#endif // LINE_H
