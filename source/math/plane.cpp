#include "plane.h"
#include "vec4.h"
#include "math.h"

namespace Math
{
    Plane::Plane() : m_normal(vec3(0,0,1)), m_distance(0) {}
	
	Plane::Plane(const Plane& plane)
	{
		if (this != &plane)
		{
			m_normal = plane.m_normal;
			m_distance = plane.m_distance;
		}
	}

    Plane::Plane(const vec3& point, const vec3& normal) : m_normal(normal)
    {
        m_distance = -normal.Dot(point);
    }

    Plane::Plane(const vec3& normal, float distances) : m_normal(normal), m_distance(distances)
    {}

    Plane::Plane(const vec3& a, const vec3& b, const vec3& c)
    {
		Set(a, b, c);
    }

	Plane& Plane::operator = (const Plane& plane)
	{
		if (this != &plane)
		{
			m_normal = plane.m_normal;
			m_distance = plane.m_distance;
		}
		return *this;
	}

	void Plane::Set(const vec3& a, const vec3& b, const vec3& c)
    {
        m_normal = (b-a).Cross(c-a).Normalized();
        m_distance = -m_normal.Dot(a);
    }

    const Plane Plane::TransformNode(const mat4 &matrix) const
    {
        vec4 p(m_normal, m_distance);
        mat4 m = matrix.Inversed().Transposed();
        vec4 res = m * p;
        return Plane(vec3(res.X(), res.Y(), res.Z()), res.W());
    }

	bool Plane::Save(std::ostream& stream) const
	{
		m_normal.Save(stream);
		stream.write((char*)&m_distance, sizeof(m_distance));
		return true;
	}

	bool Plane::Load(std::istream& stream)
	{
		m_normal.Load(stream);
		stream.read((char*)&m_distance, sizeof(m_distance));
		return true;
	}
}
