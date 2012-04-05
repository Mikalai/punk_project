#include "functions.h"
#include "line3d.h"
#include "plane.h"
#include "math.h"
#include "triangle3d.h"

namespace Math
{
	Line3D::Line3D() : m_origin(vec3(0,0,0)), m_direction(vec3(0,0,1)) {}
	Line3D::Line3D(const vec3& org, const vec3& dst) 
		: m_origin(org)
		, m_destination(dst) 
		, m_direction((org-dst).Normalized())
	{}

	Line3D::Location Line3D::Classify(const vec3& point) const
	{
		float t = (point-m_origin).Dot(m_direction);
		if (Math::abs(1.0f - Math::abs(t)) < EPS)
			return LOCATION_ON;
		return LOCATION_OUT;
	}

	const vec3 Line3D::PointAt(float t) const
	{
		return m_origin + t * (m_destination - m_origin);
	}

	Line3D::Location Line3D::Classify(const Plane &plane) const
	{
		float nd = m_direction.Dot(plane.normal);
		if (Math::abs(nd) < EPS)
		{
			Plane::Location startPointLoc = plane.Classify(m_origin);
			if (startPointLoc == Plane::ON)
				return LOCATION_BELONG;
			else
				return LOCATION_PARALLEL;
		}
		return LOCATION_CROSS;
	}


	const vec3& Line3D::Direction() const
	{
		return m_direction;
	}

	const vec3& Line3D::Origin() const
	{
		return m_origin;
	}

	void Line3D::SetOrigin(const vec3& origin)
	{
		m_origin = origin;
		m_direction = (m_destination - m_origin).Normalized();
	}

	const vec3& Line3D::Destination() const
	{
		return m_destination;
	}

	void Line3D::SetDestination(const vec3& destination)
	{
		m_destination = destination;
		m_direction = (m_destination - m_origin).Normalized();
	}

	float Line3D::SegmentLength() const
	{
		return (m_destination - m_origin).Length();
	}

	IntersectionType Line3D::CrossTriangle(const Triangle3D& p, float& t) const
	{
		vec3 a = m_origin;
		vec3 b = m_destination;
		vec3 c = p[0];
		vec3 n = p.GetNormal();
		double denom = n.Dot(b - a);
		if (denom == 0.0)
		{
			Point3DPositionClassification aclass = Math::Classify(m_origin, p);
			if (aclass != POINT3D_ON)
				return PARALLEL;
			else
				return COLLINEAR;
		}
		float num = n.Dot(a - c);
		t = -num / denom;
		return SKEW;
	}
}
