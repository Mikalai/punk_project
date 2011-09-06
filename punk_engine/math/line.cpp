#include "functions.h"
#include "line.h"
#include "plane.h"
#include "math.h"

namespace Math
{
    Line::Line() : origin(vec3(0,0,0)), direction(vec3(0,0,1)) {}
    Line::Line(vec3 org, vec3 dir) : origin(org), direction(dir) {}

    Line::Location Line::Classify(const vec3& point) const
    {
        float t = (point-origin).Dot(direction);
        if (Math::abs(1.0f - Math::abs(t)) < EPS)
            return LOCATION_ON;
        return LOCATION_OUT;
    }

    vec3 Line::PointAt(float t) const
    {
        return origin + direction * t;
    }

    Line::Location Line::Classify(const Plane &plane) const
    {
        float nd = direction.Dot(plane.normal);
        if (Math::abs(nd) < EPS)
        {
            Plane::Location startPointLoc = plane.Classify(origin);
            if (startPointLoc == Plane::ON)
				return LOCATION_BELONG;
            else
                return LOCATION_PARALLEL;
        }
        return LOCATION_CROSS;
    }

}
