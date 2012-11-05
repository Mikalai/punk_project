#include "triangle3d.h"
#include "triangle2d.h"
#include "line3d.h"
#include "helper.h"

#include <limits>

namespace Math
{
	Triangle3D::Triangle3D()
	{}

	Triangle3D::Triangle3D(const vec3& v0, const vec3& v1, const vec3& v2)
	{
		m_v[0] = v0; m_v[1] = v1; m_v[2] = v2;
		m_bbox.MinPoint().X() = Min(v0.X(), v1.X(), v2.X());
		m_bbox.MinPoint().Y() = Min(v0.Y(), v1.Y(), v2.Y());
		m_bbox.MinPoint().Z() = Min(v0.Z(), v1.Z(), v2.Z());
		m_bbox.MaxPoint().X() = Max(v0.X(), v1.X(), v2.X());
		m_bbox.MaxPoint().Y() = Max(v0.Y(), v1.Y(), v2.Y());
		m_bbox.MaxPoint().Z() = Max(v0.Z(), v1.Z(), v2.Z());
		m_normal = (v1 - v0).Cross(v2 - v0);
		m_normal.Normalize();
		m_distance = -m_normal.Dot(v0);
	}

	const vec3& Triangle3D::operator[] (unsigned i) const
	{
		return m_v[i];
	}

	vec3& Triangle3D::operator[] (unsigned i) 
	{
		return m_v[i];
	}

	const BoundingBox& Triangle3D::GetBoundingBox() const
	{
		return m_bbox;
	}

	const vec3& Triangle3D::GetNormal() const
	{
		return m_normal; 
	}

	bool Triangle3D::GetBarycentric(const vec3& p, float& w0, float& w1, float& w2) const
	{
		vec3 r = p - m_v[0];
		vec3 q1 = m_v[1] - m_v[0];
		vec3 q2 = m_v[2] - m_v[0];
		float q1_q2 = q1.Dot(q2);
		float r_q1 = r.Dot(q1);
		float r_q2 = r.Dot(q2);
		float q1_q1 = q1.Dot(q1);
		float q2_q2 = q2.Dot(q2);

		float inv_det = 1.0f / (q1_q1*q2_q2 - q1_q2*q1_q2);
		w1 = inv_det*( q2_q2*r_q1 - q1_q2*r_q2);
		w2 = inv_det*(-q1_q2*r_q2 + r_q2*q2_q2);
		w0 = 1.0f - w1 - w2;	
		return true;
	}

	const Triangle2D Triangle3D::ProjectXY() const
	{
		return Triangle2D(
			vec2(m_v[0].X(), m_v[0].Y()),
			vec2(m_v[1].X(), m_v[1].Y()),
			vec2(m_v[2].X(), m_v[2].Y()));
	}

	const Triangle2D Triangle3D::ProjectXZ() const
	{
		return Triangle2D(
			vec2(m_v[0].X(), m_v[0].Z()),
			vec2(m_v[1].X(), m_v[1].Z()),
			vec2(m_v[2].X(), m_v[2].Z()));
	}

	const Triangle2D Triangle3D::ProjectYZ() const
	{
		return Triangle2D(
			vec2(m_v[0].Y(), m_v[0].Z()),
			vec2(m_v[1].Y(), m_v[1].Z()),
			vec2(m_v[2].Y(), m_v[2].Z()));
	}
}
