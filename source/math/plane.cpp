#include "plane.h"
#include "vec4.h"
#include "math.h"

namespace Math
{
    Plane::Plane() : normal(vec3(0,0,1)), distance(0) {}
	
	Plane::Plane(const Plane& plane)
	{
		if (this != &plane)
		{
			normal = plane.normal;
			distance = plane.distance;
		}
	}

    Plane::Plane(const vec3& point, const vec3& normal) : normal(normal)
    {
        distance = -normal.Dot(point);
    }

    Plane::Plane(const vec3& normal, float distances) : normal(normal), distance(distance)
    {}

    Plane::Plane(const vec3& a, const vec3& b, const vec3& c)
    {
        normal = (b-a).Cross(c-a).Normalized();
        distance = -normal.Dot(a);
    }

	Plane& Plane::operator = (const Plane& plane)
	{
		if (this != &plane)
		{
			normal = plane.normal;
			distance = plane.distance;
		}
		return *this;
	}

	void Plane::MakeFromPoints(const vec3& a, const vec3& b, const vec3& c)
    {
        normal = (b-a).Cross(c-a).Normalized();
        distance = -normal.Dot(a);
    }

    const Plane Plane::Transform(const mat4 &matrix) const
    {
        vec4 p(normal, distance);
        mat4 m = matrix.Inversed().Transposed();
        vec4 res = m * p;
        return Plane(vec3(res.X(), res.Y(), res.Z()), res.W());
    }

}
