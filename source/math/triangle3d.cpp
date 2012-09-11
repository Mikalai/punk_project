#include "triangle3d.h"
#include "triangle2d.h"
#include "line3d.h"
#include "functions.h"

#include <limits>

namespace Math
{
	Triangle3D::Triangle3D()
	{}

	Triangle3D::Triangle3D(const vec3& v0, const vec3& v1, const vec3& v2)
	{
		m_v[0] = v0; m_v[1] = v1; m_v[2] = v2;
		m_bbox.Min().X() = min(v0.X(), v1.X(), v2.X());
		m_bbox.Min().Y() = min(v0.Y(), v1.Y(), v2.Y());
		m_bbox.Min().Z() = min(v0.Z(), v1.Z(), v2.Z());
		m_bbox.Max().X() = max(v0.X(), v1.X(), v2.X());
		m_bbox.Max().Y() = max(v0.Y(), v1.Y(), v2.Y());
		m_bbox.Max().Z() = max(v0.Z(), v1.Z(), v2.Z());
		m_normal = (v1 - v0).Cross(v2 - v0);
		m_normal.Normalize();
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

	bool Triangle3D::CrossTriangle(const Triangle3D& t)
	{
		Line3D ab(m_v[0], m_v[1]);
		Line3D bc(m_v[1], m_v[2]);
		Line3D ca(m_v[2], m_v[0]);

		Line3D de(t[0], t[1]);
		Line3D ef(t[1], t[2]);
		Line3D fd(t[2], t[0]);

		//
		//  cross firs tr with second
		//
		float s = 0;
		if (LineCrossTriangle(ab, t, s) == SKEW_CROSS)
			if (s >= 0 && s <= 1)
				return true;
		if (LineCrossTriangle(bc, t, s) == SKEW_CROSS)
			if (s >= 0 && s <= 1)
				return true;
		if (LineCrossTriangle(ca, t, s) == SKEW_CROSS)
			if (s >= 0 && s <= 1)
				return true;

		//
		//  cross second tr with firs
		//
		if (LineCrossTriangle(de, *this, s) == SKEW_CROSS)
			if (s >= 0 && s <= 1)
				return true;
		if (LineCrossTriangle(ef, *this, s) == SKEW_CROSS)
			if (s >= 0 && s <= 1)
				return true;
		if (LineCrossTriangle(fd, *this, s) == SKEW_CROSS)
			if (s >= 0 && s <= 1)
				return true;
		return false;
	}

	IntersectionType LineCrossTriangle(const Line3D& e, const Triangle3D& p, float& t)
	{
		vec3 q;
		IntersectionType aclass = e.CrossTriangle(p, t);
		if (aclass == PARALLEL || aclass == COLLINEAR)
			return aclass;
		q = e.PointAt(t);
		bool p1 = p.ProjectXY().IsPointIn(q.XY());
		bool p2 = p.ProjectXZ().IsPointIn(q.XZ());
		bool p3 = p.ProjectYZ().IsPointIn(q.YZ());
		if (p1 && p2 && p3)
			return SKEW_CROSS;
		else
			return SKEW_NO_CROSS;
	}

	Point3DPositionClassification Classify(const vec3& point, const Triangle3D& triangle)
	{
		vec3 v = point - triangle[0];
		double len = v.Length();
		if (len == 0.0)
			return POINT3D_ON;
		v.Normalize();
		double d = v.Dot(triangle.GetNormal());
		if (d > std::numeric_limits<float>().epsilon())
			return POINT3D_POSITIVE;
		else if (d < -std::numeric_limits<float>().epsilon())
			return POINT3D_NEGATIVE;
		else
			return POINT3D_ON;                
	}
}
