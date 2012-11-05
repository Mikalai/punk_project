#include "relations.h"
#include "constants.h"
#include "helper.h"
#include "vec3.h"
#include "triangle3d.h"
#include "line3d.h"
#include "plane.h"

namespace Math
{
	Relation ClassifyPoint(const Line3D& line, const vec3& point)
	{
		const vec3& org = line.Origin();
		const vec3& dst = line.Destination();
		const vec3& p = point;

		float cosa = (p-org).Dot(dst);
		if (Math::Abs(1.0f - Math::Abs(cosa)) < EPS)
		{			
			float t = (p - org).Length() / (dst - org).Length();			
			if (Math::Abs(t) < EPS)
				return Relation::START;
			if (Math::Abs(1 - t) < EPS)
				return Relation::END;
			if (t < 0)
				return Relation::FRONT;
			if (t > 1)
				return Relation::BACK;
			return Relation::INSIDE;
		}
		return Relation::OUTSIDE;
	}

	Relation ClassifyPoint(const Plane& plane, const vec3& p)
	{
		const vec3& n = plane.GetNormal();
		float dst = plane.GetDistance();

		vec3 r = (p-n*dst); // vector to the point to classify

		float cosa = r.Dot(n);

		if (cosa < -EPS)
			return Relation::BACK;
		if (cosa > EPS)
			return Relation::FRONT;
		return Relation::ON;
	}

	Relation ClassifyPoint(const vec3& p, const Triangle3D& triangle)
	{
		const vec3& n = triangle.GetNormal();
		float org_dst = triangle.GetDistance();		
		
		float dst = p.Dot(n) + org_dst;

		if (Math::Abs(dst) < EPS)	//	point on the same plane as triangle
		{
			float w0, w1, w2;
			triangle.GetBarycentric(p, w0, w1, w2);
			
			if (w0 < -EPS || w1 < -EPS || w2 < -EPS)
				return Relation::OUTSIDE;
			if (Math::Abs(1.0f - w0) < EPS)
				return Relation::A;
			if (Math::Abs(1.0f - w1) < EPS)
				return Relation::B;
			if (Math::Abs(1.0f - w2) < EPS)
				return Relation::C;
			if (Math::Abs(w0) < EPS)
				return Relation::BC;
			if (Math::Abs(w1) < EPS)
				return Relation::CA;
			if (Math::Abs(w2) < EPS)
				return Relation::AB;
			if (w0 > 0 && w1 > 0 && w2 > 0)
				return Relation::INSIDE;
			return Relation::OUTSIDE;
		}

		if (dst < 0.0f)
			return Relation::BACK;
		return Relation::FRONT;		
	}

	Relation ClassifyLine(const Line3D& line, const Plane& p)
	{
		const vec3& n = p.GetNormal();
		float org_dst = p.GetDistance();
		const vec3& dir = line.Direction();
		float v = n.Dot(dir);

		if (Math::Abs(v) < EPS)
		{
			float dst = n.Dot(line.Origin()) + org_dst;
			if (Math::Abs(dst) < EPS)
				return Relation::ON;
			if (dst < 0)
				return Relation::BACK;
			if (dst > 0)
				return Relation::FRONT;
		}

		return Relation::INTERSECT;
	}

	Relation ClassifyLine(const Line3D& line, const Triangle3D& triangle)
	{
		const vec3& org = line.Origin();
		const vec3& dst = line.Destination();
		const vec3& n = triangle.GetNormal();
		float org_dst = triangle.GetDistance();
		const vec3& dir = line.Direction();
		float v = n.Dot(dir);

		if (Math::Abs(v) < EPS)
		{
			float dst = n.Dot(org) + org_dst;
			if (Math::Abs(dst) < EPS)
				return Relation::ON;
			if (dst < 0)
				return Relation::BACK;
			if (dst > 0)
				return Relation::FRONT;
		}

		float t = - (n.Dot(org) + org_dst) / v;
		const vec3 intersect_point = line.PointAt(t);
		
		Relation res = ClassifyPoint(intersect_point, triangle);

		if (res != Relation::INSIDE)
			return Relation::INTERSECT;
		return Relation::NOT_INTERSECT;
	}

	Relation CrossLinePlane(const Line3D& line, const Plane& p, float& t) 
	{
		const vec3& org = line.Origin();
		const vec3& dst = line.Destination();	
		const vec3& n = p.GetNormal();
		float org_dst = p.GetDistance();
		const vec3& dir = line.Direction();
		float v = n.Dot(dir);

		if (Math::Abs(v) < EPS)
		{
			float dst = n.Dot(line.Origin()) + org_dst;
			if (Math::Abs(dst) < EPS)
				return Relation::ON;
			if (dst < 0)
				return Relation::BACK;
			if (dst > 0)
				return Relation::FRONT;
		}

		t = - (n.Dot(org) + org_dst) / v;		
		return Relation::INTERSECT;	
	}

	Relation CrossLinePlane(const Line3D& line, const Plane& p, vec3& point)
	{
		float t = 0;
		Relation res = CrossLinePlane(line, p, t);
		point = line.PointAt(t);
		return res;
	}

	Relation CrossLineTriangle(const Line3D& line, const Triangle3D& triangle, float& t)
	{
		const vec3& org = line.Origin();
		const vec3& dst = line.Destination();
		const vec3& n = triangle.GetNormal();
		float org_dst = triangle.GetDistance();
		const vec3& dir = line.Direction();
		float v = n.Dot(dir);

		if (Math::Abs(v) < EPS)
		{
			float dst = n.Dot(org) + org_dst;
			if (Math::Abs(dst) < EPS)
				return Relation::ON;
			if (dst < 0)
				return Relation::BACK;
			if (dst > 0)
				return Relation::FRONT;
		}

		t = - (n.Dot(org) + org_dst) / v;
		const vec3 intersect_point = line.PointAt(t);
		
		Relation res = ClassifyPoint(intersect_point, triangle);

		if (res != Relation::INSIDE)
			return Relation::INTERSECT;
		return Relation::NOT_INTERSECT;
	}

	Relation CrossLineTriangle(const Line3D& line, const Triangle3D& triangle, vec3& vec)
	{
		float t = 0;
		Relation res = CrossLineTriangle(line, triangle, t);
		vec = line.PointAt(t);
		return res;
	}

	Relation CrossThreePlane(const Plane& a, const Plane& b, const Plane& c, vec3& vec)
	{

	}

	Relation CrossPlanePlane(const Plane& a, const Plane& b, Line3D& line)
	{

	}

	Relation CrossTriangleTriangle(const Triangle3D& a, const Triangle3D& b, Line3D& line)
	{
		Line3D ab(a[0], a[1]);
		Line3D bc(a[1], a[2]);
		Line3D ca(a[2], a[0]);

		Line3D de(b[0], b[1]);
		Line3D ef(b[1], b[2]);
		Line3D fd(b[2], b[0]);

		//
		//  cross firs tr with second
		//
		float s = 0;
		if (CrossLineTriangle(ab, b, s) == Relation::INTERSECT)
			if (s >= 0 && s <= 1)
				return Relation::INTERSECT;
		if (CrossLineTriangle(bc, b, s) == Relation::INTERSECT)
			if (s >= 0 && s <= 1)
				return Relation::INTERSECT;
		if (CrossLineTriangle(ca, b, s) == Relation::INTERSECT)
			if (s >= 0 && s <= 1)
				return Relation::INTERSECT;

		//
		//  cross second tr with firs
		//
		if (CrossLineTriangle(de, b, s) == Relation::INTERSECT)
			if (s >= 0 && s <= 1)
				return Relation::INTERSECT;
		if (CrossLineTriangle(ef, b, s) == Relation::INTERSECT)
			if (s >= 0 && s <= 1)
				return Relation::INTERSECT;
		if (CrossLineTriangle(fd, b, s) == Relation::INTERSECT)
			if (s >= 0 && s <= 1)
				return Relation::INTERSECT;
		return Relation::NOT_INTERSECT;
	}
}