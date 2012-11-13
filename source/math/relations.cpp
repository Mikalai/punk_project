#include "relations.h"
#include "constants.h"
#include "helper.h"
#include "root_find.h"
#include "vec3.h"
#include "sphere.h"
#include "triangle3d.h"
#include "line3d.h"
#include "polygon3d.h"
#include "plane.h"

namespace Math
{
	Relation ClassifyPoint(const Line3D& line, const vec3& point)
	{
		const vec3& org = line.GetOrigin();
		const vec3& dst = line.GetDestination();
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
		const vec3& dir = line.GetDirection();
		float v = n.Dot(dir);

		if (Math::Abs(v) < EPS)
		{
			float dst = n.Dot(line.GetOrigin()) + org_dst;
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
		const vec3& org = line.GetOrigin();
		const vec3& dst = line.GetDestination();
		const vec3& n = triangle.GetNormal();
		float org_dst = triangle.GetDistance();
		const vec3& dir = line.GetDirection();
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
		const vec3& org = line.GetOrigin();
		const vec3& dst = line.GetDestination();	
		const vec3& n = p.GetNormal();
		float org_dst = p.GetDistance();
		const vec3& dir = line.GetDirection();
		float v = n.Dot(dir);

		if (Math::Abs(v) < EPS)
		{
			float dst = n.Dot(line.GetOrigin()) + org_dst;
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
		const vec3& org = line.GetOrigin();
		const vec3& dst = line.GetDestination();
		const vec3& n = triangle.GetNormal();
		float org_dst = triangle.GetDistance();
		const vec3& dir = line.GetDirection();
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

	Relation CrossLineSphere(const Line3D& line, const Sphere& sphere, float& t1, float& t2)
	{
		float r = sphere.GetRadius();
		const vec3 org = line.GetOrigin() - sphere.GetCenter();
		const vec3 dir = line.GetDestination() - line.GetOrigin();
		float a = dir.SquareLength();
		float b = 2 * org.Dot(dir);
		float c = org.SquareLength() - sphere.GetRadius();

		float in[] = {c, b, a};
		float out[2];
		RootFindResult res = SolveQuadric(in, out);
		if (res == RootFindResult::RESULT_NO_SOLUTION)
			return Relation::NOT_INTERSECT;
		if (res == RootFindResult::RESULT_ONE_SOLUTION)
		{
			t1 = out[0];
			return Relation::INTERSECT;
		}
		else if (res == RootFindResult::RESULT_TWO_SOLUTIONS)
		{
			t1 = out[0];
			t2 = out[1];
			return Relation::INTERSECT_2;
		}
		return Relation::NOT_INTERSECT;
	}

	Relation CrossLineSphere(const Line3D& line, const Sphere& sphere, vec3& p1, vec3& p2)
	{
		float t1, t2;
		Relation res = CrossLineSphere(line, sphere, t1, t2);
		if (res == Relation::NOT_INTERSECT)
			return Relation::NOT_INTERSECT;
		else if (res == Relation::INTERSECT_1)
		{
			p1 = line.PointAt(t1);
			return Relation::INTERSECT_1;
		}
		else if (res == Relation::INTERSECT_2)
		{
			p1 = line.PointAt(t1);
			p2 = line.PointAt(t2);
			return Relation::INTERSECT_2;
		}
		return Relation::NOT_INTERSECT;
	}

	Relation CrossThreePlane(const Plane& a, const Plane& b, const Plane& c, vec3& vec)
	{
		const vec3& n1 = a.GetNormal();
		const vec3& n2 = b.GetNormal();
		const vec3& n3 = c.GetNormal();

		mat3 m;
		m.SetRow(0, n1);
		m.SetRow(1, n2);
		m.SetRow(2, n3);

		float det = m.Determinant();

		if (Math::Abs(det) < Math::EPS)
			return Relation::NOT_INTERSECT;

		vec3 p(-a.GetDistance(), -b.GetDistance(), -c.GetDistance());
		vec = m.Inversed()*p;

		return Relation::INTERSECT;
	}

	Relation CrossPlanePlane(const Plane& a, const Plane& b, Line3D& line)
	{
		const vec3& n1 = a.GetNormal();
		const vec3& n2 = b.GetNormal();

		vec3 dir = n1.Cross(n2);

		Plane c(dir, 0);

		vec3 org;
		if (CrossThreePlane(a, b, c, org) == NOT_INTERSECT)
			return Relation::NOT_INTERSECT;

		line.SetOriginDirection(org, dir);

		return Relation::INTERSECT;
	}

	Relation CrossPlaneTriangle(const Plane& plane, const Triangle3D& tr, Line3D& line)
	{
		Relation res;
		Line3D ab(tr[0], tr[1]);
		Line3D bc(tr[1], tr[2]);
		Line3D ca(tr[2], tr[0]);

		vec3 p[2];
		vec3* cur = p;
		float t;

		res = CrossLinePlane(ab, plane, t);
		if (res == Relation::INTERSECT && t >= 0.0f && t <= 1.0f)
			(*cur = ab.PointAt(t), ++cur);
		
		res = CrossLinePlane(bc, plane, t);
		if (res == Relation::INTERSECT && t >= 0.0f && t <= 1.0f)
			(*cur = bc.PointAt(t), ++cur);

		res = CrossLinePlane(ca, plane, t);
		if (res == Relation::INTERSECT && t >= 0.0f && t <= 1.0f)
			(*cur, ca.PointAt(t), ++cur);

		if (cur == p+1)	//	we got two points
		{
			line.SetOriginDestination(p[0], p[1]);
			return Relation::INTERSECT;
		}
		return Relation::NOT_INTERSECT;
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

	Relation CrossPlanePolygon(const Plane& plane, const Polygon3D& polygon, const Polygon3D& front, const Polygon3D& back)
	{
		return Relation::NOT_INTERSECT;
	}

	Relation SplitTriangle(const Plane& splitter, const Triangle3D& t, Triangle3D front[2], Triangle3D back[2])
	{
		Plane plane(t[0], t[1], t[2]);
		float ss0 = splitter.GetNormal().Dot(t[0]) + splitter.GetDistance();
		float ss1 = splitter.GetNormal().Dot(t[1]) + splitter.GetDistance();
		float ss2 = splitter.GetNormal().Dot(t[2]) + splitter.GetDistance();
		int s0, s1, s2;

		if (Math::Abs(ss0) < Math::EPS)
			s0 = 0;
		if (Math::Abs(ss1) < Math::EPS)
			s1 = 0;
		if (Math::Abs(ss2) < Math::EPS)
			s2 = 0;

		if (s0 == 0 && s1 == 0 && s2 == 0)
			return Relation::NO_SPLIT_ON;

		if (s0 <= 0 && s1 <= 0 && s2 <= 0)
			return Relation::NO_SPLIT_BACK;

		if (s0 >= 0 && s1 >=0 && s2 >= 0)
			return Relation::NO_SPLIT_FRONT;

		Triangle3D* cur_front = front;
		Triangle3D* cur_back = back;

		if (s0 == 0)	//	split on front and back
		{
			Line3D l(t[1], t[2]);
			vec3 p;
			Relation r = CrossLinePlane(l, splitter, p);
			
			if (r != Relation::NOT_INTERSECT)
				return (out_error() << "Supposed to have a cross" << std::endl, Relation::NOT_INTERSECT);

			if (s1 <= 0 && s2 >= 0)
			{				
				(*cur_back) = Triangle3D(t[0], t[1], p);
				(*cur_front) = Triangle3D(p, t[2], t[0]);
				return Relation::SPLIT_1_FRONT_1_BACK;
			}
			else
			{
				(*cur_back) = Triangle3D(p, t[2], t[0]);
				(*cur_front) = Triangle3D(t[0], t[1], p);				
				return Relation::SPLIT_1_FRONT_1_BACK;
			}			
		}

		if (s1 == 0)	//	split on front and back
		{
			Line3D l(t[2], t[0]);
			vec3 p;
			Relation r = CrossLinePlane(l, splitter, p);
			
			if (r != Relation::NOT_INTERSECT)
				return (out_error() << "Supposed to have a cross" << std::endl, Relation::NOT_INTERSECT);

			if (s0 <= 0 && s2 >= 0)
			{
				(*cur_back) = Triangle3D(t[1], p, t[0]);
				(*cur_front) = Triangle3D(t[1], t[2], p);
				return Relation::SPLIT_1_FRONT_1_BACK;
			}
			else
			{
				(*cur_back) = Triangle3D(t[1], t[2], p);
				(*cur_front) = Triangle3D(t[1], p, t[0]);				
				return Relation::SPLIT_1_FRONT_1_BACK;
			}
		}

		if (s2 == 0)	//	split on front and back
		{
			Line3D l(t[0], t[1]);
			vec3 p;
			Relation r = CrossLinePlane(l, splitter, p);
			
			if (r != Relation::NOT_INTERSECT)
				return (out_error() << "Supposed to have a cross" << std::endl, Relation::NOT_INTERSECT);

			if (s0 <= 0 && s1 >= 0)
			{
				(*cur_back) = Triangle3D(t[2], t[0], p);
				(*cur_front) = Triangle3D(t[2], p, t[1]);
				return Relation::SPLIT_1_FRONT_1_BACK;
			}
			else
			{
				(*cur_front) = Triangle3D(t[2], t[0], p);
				(*cur_back) = Triangle3D(t[2], p, t[1]);
				return Relation::SPLIT_1_FRONT_1_BACK;
			}
		}

		const vec3* a = &t[0];
		const vec3* b = &t[1];
		const vec3* c = &t[2];
		int s = 1;

		Relation result = Relation::SPLIT_1_FRONT_2_BACK;

		//	common case
		if (s1 < 0 && s2 < 0 || s1 > 0 && s2 > 0)
		{
			a = &t[0];
			b = &t[1];
			c = &t[2];
			s = s0;
		}

		if (s2 < 0 && s0 < 0 || s2 > 0 && s0 > 0)
		{
			a = &t[1];
			b = &t[2];
			c = &t[0];
			s = s1;
		}

		if (s0 < 0 && s1 < 0 || s0 > 0 && s1 > 0)
		{
			a = &t[2];
			b = &t[0];
			c = &t[1];
			s = s2;
		}

		if (s1 < 0)
		{
			std::swap(cur_front, cur_back);
			result = Relation::SPLIT_2_FRONT_1_BACK;
		}


		const Line3D ab(*a, *b);
		const Line3D ac(*a, *c);

		vec3 bb, cc;
		Relation r = CrossLinePlane(ab, splitter, bb);
		if (r == Relation::NOT_INTERSECT)
			return (out_error() << "Supposed to have intersection" << std::endl, Relation::NOT_INTERSECT);

		r = CrossLinePlane(ac, splitter, cc);
		if (r == Relation::NOT_INTERSECT)
			return (out_error() << "Supposed to have intersection" << std::endl, Relation::NOT_INTERSECT);

		*cur_front = Triangle3D(*a, bb, cc);
		*cur_back++ = Triangle3D(bb, *b, *c);
		*cur_back = Triangle3D(bb, *c, cc);

		return result;
	}
}