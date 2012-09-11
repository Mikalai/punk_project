#include "plane.h"
#include "vec4.h"
#include "functions.h"
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

    Plane::Location Plane::Classify(const vec3& p) const
    {
        vec3 r = (p-normal*distance); // vector to the point to classify
        float cosa = r.Dot(normal);
        if (cosa < -EPS)
            return BACK;
        if (cosa > EPS)
            return FRONT;
        return ON;
    }

    float Plane::Distance(const vec3& p) const
    {
		return normal.Dot(p) + distance;
    }

    Plane Plane::Transform(const mat4 &matrix) const
    {
        vec4 p(normal, distance);
        mat4 m = matrix.Inversed().Transposed();
        vec4 res = m * p;
        return Plane(vec3(res.X(), res.Y(), res.Z()), res.W());
    }

}
