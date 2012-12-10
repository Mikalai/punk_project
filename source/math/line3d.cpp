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
		, m_direction((dst-org).Normalized())
	{}

	const vec3 Line3D::PointAt(float t) const
	{
		return m_origin + t * (m_destination - m_origin);
	}

	void Line3D::SetOrigin(const vec3& origin)
	{
		m_origin = origin;
		m_direction = (m_destination - m_origin).Normalized();
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

	Line3D& Line3D::SetOriginDirection(const vec3& org, const vec3& dir)
	{
		m_origin = org;
		m_direction = dir;
		m_destination = m_origin + m_direction;
		return *this;
	}

	Line3D& Line3D::SetOriginDestination(const vec3& org, const vec3& dst)
	{
		m_origin = org;
		m_destination = dst;
		m_direction = (m_destination - m_origin).Normalized();
		return *this;
	}
}
