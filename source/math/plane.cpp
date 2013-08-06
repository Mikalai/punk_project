#include "plane.h"
#include "vec4.h"
#include "math.h"

namespace Math
{
	Plane::Plane() : m_plane(0, 0, 0, 0) {}
	
	Plane::Plane(const Plane& plane)
	{
		if (this != &plane)
		{
			m_plane = plane.m_plane;
		}
	}

	Plane::Plane(const vec3& point, const vec3& normal)
    {
		auto dst = -normal.Dot(point);
		m_plane.Set(normal[0], normal[1], normal[2], dst);
    }

	Plane::Plane(const vec3& normal, float distances) : m_plane(normal[0], normal[1], normal[2], distances)
    {}

    Plane::Plane(const vec3& a, const vec3& b, const vec3& c)
    {
		Set(a, b, c);
    }

	Plane::Plane(float a, float b, float c, float d)
	{
		Set(a, b, c, d);
	}

	Plane::Plane(const vec4& plane)
		: m_plane(plane)
	{}

	Plane& Plane::operator = (const Plane& plane)
	{
		if (this != &plane)
		{
			m_plane = plane.m_plane;
		}
		return *this;
	}

    Plane& Plane::Set(const vec3& a, const vec3& b, const vec3& c)
    {
		auto normal = (b-a).Cross(c-a).Normalized();
		auto distance = -normal.Dot(a);
        m_plane.Set(normal[0], normal[1], normal[2], distance);
        return *this;
    }

    const Plane Plane::TransformNode(const mat4 &matrix) const
    {        
        mat4 m = matrix.Inversed().Transposed();
		vec4 res = m * m_plane;
		return Plane(res);
    }

    void Plane::Save(System::Buffer *buffer) const
	{
        m_plane.Save(buffer);
	}

    void Plane::Load(System::Buffer *buffer)
	{
        m_plane.Load(buffer);
	}

    Plane& Plane::Set(float a, float b, float c, float d)
	{		
        m_plane.Set(a, b, c, d);
        return *this;
	}

    Plane& Plane::Set(const Line3D& line, const Math::vec3& point)
    {
        const vec3 v = (point - line.GetOrigin()).Normalized();
		auto normal = line.GetDirection().Cross(v).Normalized();
		float distance = -normal.Dot(point);
        return Set(normal, distance);
    }

    Plane& Plane::Set(const vec3 &normal, float dst)
	{
        m_plane.Set(normal[0], normal[1], normal[2], dst);
        return *this;
	}

    Plane& Plane::Set(const vec4& value)
	{
		m_plane = value;
        return *this;
	}

    const vec3 Plane::GetNormal() const
	{
        return m_plane.XYZ();
	}

	float Plane::GetDistance() const
	{
		return m_plane.W();
	}

	const vec4& Plane::AsVector() const
	{
		return m_plane;
	}

	float operator * (const Plane& plane, const vec3& v)
	{
		float res = plane.AsVector().Dot(vec4(v, 1));
		return res;
	}

	float operator * (const Plane& plane, const vec4& v)
	{
		float res = plane.AsVector().Dot(v);
		return res;
	}

	const Plane operator * (const mat4& m, const Plane& p)
	{
		Plane res(m * p.AsVector());
		return res;
	}

    const System::string Plane::ToString() const
    {
        return m_plane.ToString();
    }

    Plane& Plane::Normalize()
    {
        float f = 1.0f / vec3(m_plane.XYZ()).Length();
        m_plane *= f;
        return *this;
    }
}
