#include <set>
#include "../system/logger.h"
#include "vec2.h"
#include "mat2.h"
#include "low_level_math.h"
#include <limits>
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
#include "ellipsoid.h"
#include "portal.h"
#include "clip_space.h"
#include "bounding_box.h"
#include "convex_shape_mesh.h"
#include "frustum.h"
#include "triangle2d.h"
#include "frustum_plane.h"
#include "frustum_points.h"

namespace Math
{
	Relation ClassifyPoint(const Line3D& line, const vec3& point)
	{
		const vec3 org = line.GetOrigin();
		const vec3 dst = line.GetDestination();
		const vec3 p = point;

		float cosa = (p-org).Dot(dst);
        if (Math::Abs(1.0f - Math::Abs(cosa)) < Eps)
		{
			float t = (p - org).Length() / (dst - org).Length();
            if (Math::Abs(t) < Eps)
				return Relation::START;
            if (Math::Abs(1 - t) < Eps)
				return Relation::END;
			if (t < 0)
				return Relation::FRONT;
			if (t > 1)
				return Relation::BACK;
			return Relation::INSIDE;
		}
		return Relation::OUTSIDE;
	}

	Relation ClassifyPoint(const vec3& p, const Plane& plane)
	{
		auto s = plane * p;
        if (s < -Eps)
			return Relation::BACK;
        if (s > Eps)
			return Relation::FRONT;
		return Relation::ON;
	}

	Relation ClassifyPoint(const vec3& p, const Triangle3D& triangle)
	{
		const vec3 n = triangle.GetNormal();
		float org_dst = triangle.GetDistance();

		float dst = p.Dot(n) + org_dst;

        if (Math::Abs(dst) < Eps)	//	point on the same plane as triangle
		{
			float w0, w1, w2;
			triangle.GetBarycentric(p, w0, w1, w2);

            if (w0 < -Eps || w1 < -Eps || w2 < -Eps)
				return Relation::OUTSIDE;
            if (Math::Abs(1.0f - w0) < Eps)
				return Relation::A;
            if (Math::Abs(1.0f - w1) < Eps)
				return Relation::B;
            if (Math::Abs(1.0f - w2) < Eps)
				return Relation::C;
            if (Math::Abs(w0) < Eps)
				return Relation::BC;
            if (Math::Abs(w1) < Eps)
				return Relation::CA;
            if (Math::Abs(w2) < Eps)
				return Relation::AB;
			if (w0 > 0 && w1 > 0 && w2 > 0)
				return Relation::INSIDE;
			return Relation::OUTSIDE;
		}

		if (dst < 0.0f)
			return Relation::BACK;
		return Relation::FRONT;
	}

	Relation ClassifyPoint(const vec3& point, const BoundingBox& bbox)
	{
		for (int i = 0; i < 6; ++i)
		{
			const Plane p = bbox.GetPlane(i);
			Relation relation = ClassifyPoint(point, p);
			if (relation == Relation::BACK)
				return Relation::OUTSIDE;
		}
		return Relation::INSIDE;
	}

	Relation ClassifyPoint(const vec3& point, const BoundingSphere& sphere)
	{
		float sqr_dst = (point - sphere.GetCenter()).SquareLength();
		float r = sphere.GetRadius();
		if (sqr_dst > r*r)
			return Relation::OUTSIDE;
		return Relation::INSIDE;
	}

    Relation ClassifyPoint(const vec3& point, const FrustumCore& frustum)
	{
        Plane p[6];
        ProjectionMatrixToPlanes(FrustumCreatePerspectiveProjectionMatrix(frustum), p);
		for (int i = 0; i != 6; ++i)
		{            
            if (ClassifyPoint(point, p[i]) == Relation::BACK)
				return Relation::OUTSIDE;
		}
		return Relation::INSIDE;
	}

	Relation ClassifyPoint(const vec3& point, const ClipSpace& space)
	{
		for (size_t i = 0; i != space.size(); ++i)
		{
			auto r = ClassifyPoint(point, space[i]);
			if (r == BACK)
				return OUTSIDE;

		}
		return INSIDE;
	}

	Relation ClassifyPoint(const vec3& point, const ConvexShapeMesh& mesh)
	{
		Relation relation = ClassifyPoint(point, mesh.GetBoundingSphere());
		if (relation == Relation::OUTSIDE)
			return Relation::OUTSIDE;

		relation = ClassifyPoint(point, mesh.GetBoundingBox());
		if (relation == Relation::OUTSIDE)
			return Relation::OUTSIDE;

		const ConvexShapeMesh::PointsCollection& points = mesh.GetPoints();
		const ConvexShapeMesh::FacesCollection& faces = mesh.GetFaces();
		const ConvexShapeMesh::NormalsCollection& normals = mesh.GetNormals();

		for (int i = 0; i < (int)faces.size(); ++i)
		{
			Plane p(points[faces[i][0]], normals[i]);
			Relation relation = ClassifyPoint(point, p);
			if (relation == Relation::BACK)
				return Relation::OUTSIDE;
		}
		return Relation::INSIDE;
	}

	Relation ClassifyLine(const Line3D& line, const Plane& p)
	{
		const vec3 n = p.GetNormal();
		float org_dst = p.GetDistance();
		const vec3 dir = line.GetDirection();
		float v = n.Dot(dir);

        if (Math::Abs(v) < Eps)
		{
			float dst = n.Dot(line.GetOrigin()) + org_dst;
            if (Math::Abs(dst) < Eps)
				return Relation::ON;
			if (dst < 0)
				return Relation::BACK;
			if (dst > 0)
				return Relation::FRONT;
		}

		return Relation::INTERSECT;
	}

	Relation ClassifyLine(const Line3D& line, const ClipSpace& space)
	{

	}

	Relation ClassifyLine(const Line3D& line, const Triangle3D& triangle)
	{
		const vec3 org = line.GetOrigin();
		const vec3 n = triangle.GetNormal();
		float org_dst = triangle.GetDistance();
		const vec3 dir = line.GetDirection();
		float v = n.Dot(dir);

        if (Math::Abs(v) < Eps)
		{
			float dst = n.Dot(org) + org_dst;
            if (Math::Abs(dst) < Eps)
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

	//	Bounding box should be in clip space
	Relation ClassifyBoudingBox(const BoundingBox& bbox, const ClipSpace& clipper)
	{
		if (bbox.GetR().Length() > 4*bbox.GetS().Length() && bbox.GetR().Length() > 4*bbox.GetT().Length())
		{
			vec3 q1 = bbox.GetCenter() - 0.5f * bbox.GetR();
			vec3 q2 = bbox.GetCenter() + 0.5f * bbox.GetR();

			for (const auto& plane : clipper)
			{
				const vec3 n = plane.GetNormal();
                float r_eff = 0.5f * ( Abs(n.Dot(bbox.GetS())) + Abs(n.Dot(bbox.GetT())));

				float r1 = plane * q1;
				float r2 = plane * q2;

				if (r1 <= r_eff && r2 <= r_eff)
					return Relation::NOT_VISIBLE;

				if (r1 >= r_eff && r2 >= r_eff)
					continue;

				float t = (r_eff + plane * q1) / (plane * (q1 - q2));
				const vec3 q3 = q1 + t*(q2-q1);

				if (r1 <= r_eff)
					q1 = q3;

				if (r2 <= r_eff)
					q2 = q3;
			}
			return Relation::VISIBLE;
		}
		else
		{
			for (const auto& plane : clipper)
			{
				const vec3 n = plane.GetNormal();
                float r_eff = 0.5f * (Abs(n.Dot(bbox.GetR())) + Abs(n.Dot(bbox.GetS())) + Abs(n.Dot(bbox.GetT())));

				float value = plane * bbox.GetCenter();
				if (value < -r_eff)
					return Relation::NOT_VISIBLE;
			}
			return Relation::VISIBLE;
		}
	}

	Relation ClassifyBoudingSphere(const Sphere& sphere, const ClipSpace& clipper)
	{
		const vec3 q = sphere.GetCenter();
		for (const auto& plane : clipper)
		{
			float r = plane * q;
			if (r <= -sphere.GetRadius())
				return Relation::NOT_VISIBLE;
		}
		return Relation::VISIBLE;
	}

	Relation CrossLineLine(const Line3D& line1, const Line3D& line2, float& t1, float& t2, float& dst)
	{
		auto s1 = line1.GetOrigin();
		auto v1 = line1.GetDestination() - line1.GetOrigin();
		auto s2 = line2.GetOrigin();
		auto v2 = line2.GetDestination() - line2.GetOrigin();

		float k = powf(v1.Dot(v2), 2.0f) - v1.SquareLength()*v2.SquareLength();
		if (fabs(k) < 1e-6)
			return Relation::PARALLEL;
		k = 1.0f / k;

		float minus_v2_v2 = -v2.Dot(v2);
		float v1_v2 = v1.Dot(v2);
		float minus_v1_v2 = -v1.Dot(v2);
		float v1_v1 = v1.Dot(v1);
		mat2 m;
		m[0] = minus_v2_v2;
		m[1] = minus_v1_v2;
		m[2] = v1_v2;
		m[3] = v1_v1;

		m = mat2(-v2.SquareLength(), v1.Dot(v2), -v1.Dot(v2), v1.SquareLength());
		m *= k;

		vec2 v((s2 - s1).Dot(v1), (s2 - s1).Dot(v2));
		vec2 res =  m * v;
		t1 = res[0];
		t2 = res[1];

		auto p1 = line1.PointAt(t1);
		auto p2 = line2.PointAt(t2);

		dst = (p1 - p2).Length();

		if (dst < 1e-6)
			return Relation::INTERSECT;

		return Relation::NOT_INTERSECT;
	}

	Relation CrossLineLine(const Line3D& line1, const Line3D& line2, vec3& p)
	{
		float t1;
		float t2;
		float dst;
		auto res = CrossLineLine(line1, line2, t1, t2, dst);
		if (res == INTERSECT)
		{
			auto p1 = line1.PointAt(t1);
			auto p2 = line2.PointAt(t2);
            p = 0.5f * (p1 + p2);
		}
		return res;
	}

	Relation CrossLinePlane(const Line3D& line, const Plane& p, float& t)
	{
		const vec3 org = line.GetOrigin();
		const vec3 dst = line.GetDestination();
		const vec3 dir = dst - org;
		float v = p * vec4(dir, 0);
		float distance = p * org;

        if (Math::Abs(v) < Eps)
		{
            if (Math::Abs(distance) < Eps)
				return Relation::ON;
			if (distance < 0)
				return Relation::BACK;
			if (distance > 0)
				return Relation::FRONT;
		}
		t = - distance / v;
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
		const vec3 org = line.GetOrigin();
		const vec3 n = triangle.GetNormal();
		float org_dst = triangle.GetDistance();
        const vec3 dir = line.GetDestination() - line.GetOrigin();
		float v = n.Dot(dir);

        if (Math::Abs(v) < Eps)
		{
			float dst = n.Dot(org) + org_dst;
            if (Math::Abs(dst) < Eps)
				return Relation::ON;
			if (dst < 0)
				return Relation::BACK;
			if (dst > 0)
				return Relation::FRONT;
		}

		t = - (n.Dot(org) + org_dst) / v;
		const vec3 intersect_point = line.PointAt(t);

		Relation res = ClassifyPoint(intersect_point, triangle);

        if (res == Relation::INSIDE)
			return Relation::INTERSECT;
		return Relation::NOT_INTERSECT;
	}

	Relation CrossLineTriangle(const Line3D& line, const Triangle3D& triangle, vec3& vec)
	{
        float t= 0;
		Relation res = CrossLineTriangle(line, triangle, t);
		vec = line.PointAt(t);
		return res;
	}

    Relation CrossLineTriangles(const Line3D &line, const std::vector<vec3> &point, const std::vector<ivec3> &faces, std::vector<vec3> &res_points, std::vector<size_t> &res_faces)
    {
        res_faces.clear();
        res_points.clear();
        for (size_t i = 0; i != faces.size(); ++i)
        {
            const ivec3& face = faces[i];
            const vec3& p0 = point[face[0]];
            const vec3& p1 = point[face[1]];
            const vec3& p2 = point[face[2]];

            const Triangle3D triangle(p0, p1, p2);
            float t;
            Relation res = CrossLineTriangle(line, triangle, t);
            if (res == Relation::INTERSECT)
            {
                res_points.push_back(line.PointAt(t));
                res_faces.push_back(i);
            }
        }
        if (res_faces.empty())
            return Relation::NOT_INTERSECT;
        return Relation::INTERSECT;
    }

	Relation CrossLineSphere(const Line3D& line, const Sphere& sphere, float& t1, float& t2)
	{
		const vec3 org = line.GetOrigin() - sphere.GetCenter();
		const vec3 dir = line.GetDestination() - line.GetOrigin();
		float a = dir.SquareLength();
		float b = 2 * org.Dot(dir);
		float c = org.SquareLength() - sphere.GetRadius()*sphere.GetRadius();

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

	Relation CrossLineEllipsoid(const Line3D& line, const Ellipsoid& ellipsoid, float& t1, float& t2)
	{
		float m = ellipsoid.GetRadiusX() / ellipsoid.GetRadiusY();
		float n = ellipsoid.GetRadiusX() / ellipsoid.GetRadiusZ();
		float r = ellipsoid.GetRadiusX();

		const vec3 s = line.GetOrigin() - ellipsoid.GetCenter();
		const vec3 v = line.GetDestination() - line.GetOrigin();

		float a = v[0]*v[0] + m*m*v[1]*v[1] + n*n*v[2]*v[2];
		float b = 2*(s[0]*v[0] + m*m*s[1]*v[1] + n*n*s[2]*v[2]);
		float c = s[0]*s[0] + m*m*s[1]*s[1] + n*n*s[2]*s[2] - r*r;

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

	Relation CrossLineEllipsoid(const Line3D& line, const Ellipsoid& ellipsoid, vec3& p1, vec3& p2)
	{
		float t1, t2;
		Relation res = CrossLineEllipsoid(line, ellipsoid, t1, t2);
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

	Relation CrossLineConvexShape(const Line3D& line, const ConvexShapeMesh& mesh, float& t1, float& t2, int& face1, int& face2)
	{
		const ConvexShapeMesh::PointsCollection& points = mesh.GetPoints();
		const ConvexShapeMesh::FacesCollection& faces = mesh.GetFaces();

		Relation result[] = {Relation::NOT_INTERSECT, Relation::INTERSECT_1, Relation::INTERSECT_2};
		int* res_face[] = {&face1, &face2};
		float* res_params[] = {&t1, &t2};

		float** cur_param = res_params;
		Relation* cur_result = result;
		int** cur_face = res_face;

		for (int i = 0; i < (int)faces.size(); ++i)
		{
			Triangle3D t(points[faces[i][0]], points[faces[i][1]], points[faces[i][2]]);
			Relation res = CrossLineTriangle(line, t, **cur_param);
			if (res == Relation::INTERSECT)
			{
				cur_param++;
				cur_result++;
				**cur_face = i;
				cur_face++;

				if (*cur_result == Relation::INTERSECT_2)
					return Relation::INTERSECT_2;
			}
		}
		return *cur_result;
	}

	Relation CrossLineConvexShape(const Line3D& line, const ConvexShapeMesh& shape, vec3& p1, vec3& p2, int& face_index1, int& face_index2)
	{
		float t1, t2;
		auto res = CrossLineConvexShape(line, shape, t1, t2, face_index1, face_index2);
		if (res == Relation::NOT_INTERSECT)
			return res;
		if (res == Relation::INTERSECT_1)
		{
			p1 = line.PointAt(t1);
			return res;
		}

		if (res == Relation::INTERSECT_2)
		{
			p1 = line.PointAt(t1);
			p2 = line.PointAt(t2);
			return res;
		}
		return Relation::NOT_INTERSECT;
	}

	Relation CrossThreePlane(const Plane& a, const Plane& b, const Plane& c, vec3& vec)
	{
		Line3D line;
		if (CrossPlanePlane(a, b, line) != Relation::INTERSECT)
			return Relation::NOT_INTERSECT;

		return CrossLinePlane(line, c, vec);
	}

	Relation CrossPlanePlane(const Plane& a, const Plane& b, Line3D& line)
	{
		const vec3 n1 = a.GetNormal();
		const vec3 n2 = b.GetNormal();

        if (fabs(n1.Dot(n2)) > 1.0f - Math::Eps)
            return NOT_INTERSECT;

		vec3 dir = n1.Cross(n2).Normalized();

		Plane c(dir, 0);

		const vec3 n3 = c.GetNormal();

		mat3 m;
		m.SetRow(0, n1);
		m.SetRow(1, n2);
		m.SetRow(2, n3);

		float det = m.Determinant();

        if (Math::Abs(det) < Math::Eps)
			return Relation::NOT_INTERSECT;

		vec3 p(-a.GetDistance(), -b.GetDistance(), -c.GetDistance());
		vec3 org = m.Inversed()*p;

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
			(*cur = ca.PointAt(t), ++cur);

		if (cur == p+1)	//	we got two points
		{
			line.SetOriginDestination(p[0], p[1]);
			return Relation::INTERSECT;
		}
		return Relation::NOT_INTERSECT;
	}

	Relation CrossTriangleTriangle(const Triangle3D& a, const Triangle3D& b, Line3D& /*line*/)
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
		(void)plane; (void)polygon; (void)front; (void)back;
        throw System::PunkNotImplemented();
	}

	Relation SplitTriangle(const Plane& splitter, const Triangle3D& t, Triangle3D front[2], Triangle3D back[2])
	{
		Plane plane(t[0], t[1], t[2]);
		float ss0 = splitter.GetNormal().Dot(t[0]) + splitter.GetDistance();
		float ss1 = splitter.GetNormal().Dot(t[1]) + splitter.GetDistance();
		float ss2 = splitter.GetNormal().Dot(t[2]) + splitter.GetDistance();
		int s0, s1, s2;

        if (Math::Abs(ss0) < Math::Eps)
			s0 = 0;
        if (Math::Abs(ss1) < Math::Eps)
            s1 = 0;
        if (Math::Abs(ss2) < Math::Eps)
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

		Relation result = Relation::SPLIT_1_FRONT_2_BACK;

		//	common case
		if ((s1 < 0 && s2 < 0) || (s1 > 0 && s2 > 0))
		{
			a = &t[0];
			b = &t[1];
			c = &t[2];
		}

		if ((s2 < 0 && s0 < 0) || (s2 > 0 && s0 > 0))
		{
			a = &t[1];
			b = &t[2];
			c = &t[0];
		}

		if ((s0 < 0 && s1 < 0) || (s0 > 0 && s1 > 0))
		{
			a = &t[2];
			b = &t[0];
			c = &t[1];
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

	//	clipping should be performed in camera space
	Relation ClipPortal(const ClipSpace& clipper, const Portal& portal, Portal& clipped_portal, ClipSpace& reduced_frustum)
	{
		//	check negative side of the portal
		if (portal.GetDistance() < 0)
		{
			//out_message() << "PORTAL NOT VISIBLE" << std::endl;
			return Relation::NOT_VISIBLE;
		}

		bool partial_visible = false;
		Portal temp(portal);
        FrustumPlane p = (FrustumPlane)0;
		for (const auto& plane : clipper)
		{
			std::vector<int> in_points; in_points.reserve(portal.size());
			std::vector<int> out_points; out_points.reserve(portal.size());
			std::vector<int> on_points; on_points.reserve(portal.size());
			std::vector<Relation> flags; flags.reserve(portal.size());

			for (int i = 0; i < (int)temp.size(); ++i)
			{
				const vec3& point = temp[i];
				auto dst = plane * point;

				if (dst < - 0.001)	//	back
				{
					out_points.push_back(i);
					flags.push_back(Relation::BACK);
				}
				else if (dst > 0)
				{
					in_points.push_back(i);
					flags.push_back(Relation::FRONT);
				}
				else
				{
					on_points.push_back(i);
					flags.push_back(Relation::ON);
				}
			}

			//	if no points inside than portal is invisible
			if (in_points.empty() && !out_points.empty())
			{
				//	out_message() << "PORTAL NOT VISIBLE" << std::endl;
				return Relation::NOT_VISIBLE;
			}

			//	if no points outside than portal is visible
			if (out_points.empty())
			{
				//	out_message() << "PORTAL VISIBLE" << std::endl;
				continue;
			}

			// otherwise portal should be clipped
			//	out_message() << "PORTAL PARTIALLY VISIBLE" << std::endl;
			int mod = temp.size();
			Portal::PointsCollection new_points;
			for (int i = 0; i < (int)temp.size(); ++i)
			{
				if (flags[i] == Relation::FRONT || flags[i] == Relation::ON)
					new_points.push_back(temp[i]);

				if (flags[i] == Relation::FRONT && flags[(i + 1) % mod] == Relation::BACK)
				{
					vec3 new_point;
					CrossLinePlane(Line3D(temp[i], temp[(i+1) % mod]), plane, new_point);
					new_points.push_back(new_point);
				}

				if (flags[i] == Relation::BACK && flags[(i + 1) % mod] == Relation::FRONT)
				{
					vec3 new_point;
					CrossLinePlane(Line3D(temp[i], temp[(i+1) % mod]), plane, new_point);
					new_points.push_back(new_point);
				}
			}

            p = (FrustumPlane)((int)p + 1);
			temp.SetPoints(new_points);
		}

		//	create reduced frustum
		int mod = (int)temp.size();
		for (int i = 0; i < (int)temp.size(); ++i)
		{
			const vec3 p0 = temp[i];
			const vec3 p1 = temp[(i+1) % mod];

			const vec3 normal = p0.Cross(p1).Normalized();
			Plane p(normal, 0);

			reduced_frustum.Add(p);
		}

		if (partial_visible)
			return Relation::PARTIALLY_VISIBLE;

		clipped_portal = temp;  //  TODO: Check this statement

		return Relation::VISIBLE;
	}

	Relation Distance(const Line3D& line1, const Line3D& line2, float& dst, float& t1, float& t2)
	{
		const vec3 s1 = line1.GetOrigin();
		const vec3 s2 = line2.GetOrigin();
		const vec3 v1 = line1.GetDestination() - line1.GetOrigin();
		const vec3 v2 = line2.GetDestination() - line2.GetOrigin();

		float v1_dot_v2 = v1.Dot(v2);
		float v1_dot_v1 = v1.SquareLength();
		float v2_dot_v2 = v2.SquareLength();
		float ds_dot_v1 = (s2 - s1).Dot(v1);
		float ds_dot_v2 = (s2 - s1).Dot(v2);

		t1 = (-v2_dot_v2 * ds_dot_v1 + v1_dot_v2 * ds_dot_v2) / (v1_dot_v2 * v1_dot_v2 - v1_dot_v1 * v2_dot_v2);
		t2 = ( v1_dot_v1 * ds_dot_v2 - v1_dot_v2 * ds_dot_v1) / (v1_dot_v2 * v1_dot_v2 - v1_dot_v1 * v2_dot_v2);

		const vec3 p1 = line1.PointAt(t1);
		const vec3 p2 = line2.PointAt(t2);

		dst = (p1 - p2).Length();

		if (dst < 0.0001)
			return Relation::INTERSECT;

		return Relation::NOT_INTERSECT;
	}

	Relation Distance(const Line3D& line, const Math::vec3& point, float& dst)
	{
		const Math::vec3 q = point;
		const Math::vec3 s = line.GetOrigin();
		const Math::vec3 v = line.GetDestination() - line.GetOrigin();

		auto qs = q - s;
		auto qs_dot_v = qs.Dot(v);
		dst = sqrt(qs.Dot(qs) - qs_dot_v * qs_dot_v / v.SquareLength());

		if (dst < 1e-6)
			return Relation::INSIDE;
		return Relation::OUTSIDE;
	}

	Relation CrossSphereSphere(const Sphere& a, const Sphere& b)
	{
		float dst = a.GetRadius() + b.GetRadius();
		float sqr_dst = dst * dst;
		float cur_dst = (a.GetCenter() - b.GetCenter()).SquareLength();
		if (cur_dst < sqr_dst)
			return Relation::INTERSECT;
		return Relation::NOT_INTERSECT;
	}

	Relation CrossLines(const std::vector<Line3D>& lines, std::vector<vec3>& points)
	{
		points.clear();
		size_t count = lines.size();
		for (size_t i = 0; i != count-1; ++i)
		{
			for (size_t j = i+1; j != count; ++j)
			{
				vec3 point;
				if (INTERSECT == CrossLineLine(lines[i], lines[j], point))
				{
					points.push_back(point);
				}
			}
		}
		if (points.empty())
			return Relation::NOT_INTERSECT;
		return Relation::INTERSECT;
	}

	PUNK_ENGINE_API Relation CrossPlanes(const std::vector<Plane>& planes, std::vector<Line3D>& lines)
	{
		size_t size = planes.size();
		for (int i = 0; i != size; ++i)
		{
			for (int j = i+1; j != size; ++j)
			{
				Math::Line3D line;
				auto res = Math::CrossPlanePlane(planes[i], planes[j], line);
				if (res == Math::INTERSECT)
					lines.push_back(line);
			}
		}
		if (lines.empty())
			return NOT_INTERSECT;
		return INTERSECT;
	}

	PUNK_ENGINE_API Relation ClipExteriorLine(const Line3D& line, const Plane& plane, Line3D& ray)
	{
		auto org = line.GetOrigin();
		auto dst = line.GetDestination();
		auto dir = line.GetDirection();
		auto normal = plane.GetNormal();
		auto s = dir.Dot(normal);
		auto org_relative = ClassifyPoint(org, plane);
		auto dst_relative = ClassifyPoint(dst, plane);

		//	find intersection point
		float t;
		if (CrossLinePlane(line, plane, t) != INTERSECT)
			return NOT_INTERSECT;

		if (t < 0 || t > 1)
			return NOT_INTERSECT;

		//	line segment on negative halfplane (1)
        if (s <= 0 &&  org_relative == BACK)
			return NOT_INTERSECT;

		//	line segment on negative halfplane (2)
		if (s >= 0 && dst_relative == BACK)
			return NOT_INTERSECT;

		//	clip line segment to put dst on the plane (3)
        if (s <= 0 && dst_relative == FRONT)
		{
			auto new_dst = line.PointAt(t);
			ray.SetOriginDestination(org, new_dst);
			return INTERSECT;
		}

		// clip line segment to put origin on the plane (4)
		if (s >= 0 && org_relative == FRONT)
		{
			auto new_org = line.PointAt(t);
			ray.SetOriginDestination(new_org, dst);
			return INTERSECT;
		}

		//	(5)
		if (org_relative == FRONT && dst_relative == BACK)
		{
			auto new_dst = line.PointAt(t);
			ray.SetOriginDestination(org, new_dst);
			return INTERSECT;
		}

		//	(6)
		if (org_relative == BACK && dst_relative == FRONT)
		{
			auto new_org = line.PointAt(t);
			ray.SetOriginDestination(new_org, dst);
			return INTERSECT;
		}

		ray = line;

		return INTERSECT;
	}

    Relation CrossCircleTrianglesProjection(const std::vector<vec3>& point, const std::vector<ivec3>& faces, const Math::vec3& center, float radius)
    {
        for (const Math::ivec3& f : faces)
        {
            const Math::vec3& p0 = point[f[0]];
            const Math::vec3& p1 = point[f[1]];
            const Math::vec3& p2 = point[f[2]];

            auto c = (p0 + p1 + p2) * 0.33333333f;
            if ((c - center).Length() < radius)
                return Relation::INTERSECT;
        }
        return Relation::NOT_INTERSECT;
    }

    Relation CrossLineAxisAlignedBox(const Line3D& line, const AxisAlignedBox& a, float& tmin, vec3& q)
    {
        auto p = line.GetOrigin();
        auto d = line.GetDestination() - line.GetOrigin();
        tmin = -std::numeric_limits<float>::max();
        float tmax = std::numeric_limits<float>::max();
        for (int i = 0; i < 3; ++i)
        {
            if (fabs(d[i]) < Eps)
            {
                if (p[i] < a.MinPoint()[i] || p[i] > a.MaxPoint()[i])
                    return Relation::NOT_INTERSECT;
            }
            else
            {
                float ood = 1.0f / d[i];
                float t1 = (a.MinPoint()[i] - p[i]) * ood;
                float t2 = (a.MaxPoint()[i] - p[i]) * ood;

                if (t1 > t2)
                    std::swap(t1, t2);
                tmin = std::max(tmin, t1);
                tmax = std::min(tmax, t2);

                if (tmin > tmax)
                    return Relation::NOT_INTERSECT;
            }
        }
        q = p + d * tmin;
        return Relation::INTERSECT;
    }

    Relation CrossLineBoundingBox(const Line3D& line, const BoundingBox& bbox, vec3& p)
    {
        mat4 t;
        t.SetColumn(0, vec4(bbox.GetR(), 0));
        t.SetColumn(1, vec4(bbox.GetS(), 0));
        t.SetColumn(2, vec4(bbox.GetT(), 0));
        t.SetColumn(3, vec4(bbox.GetMinCorner().X(), bbox.GetMinCorner().Y(), bbox.GetMinCorner().Z(),1));

        auto l = t.Inversed() * line;

        AxisAlignedBox aabb;
        aabb.Set(vec3(0,0,0), vec3(bbox.GetR().Length(), bbox.GetS().Length(), bbox.GetT().Length()));
        float tmin;
        if (Relation::NOT_INTERSECT == CrossLineAxisAlignedBox(l, aabb, tmin, p))
            return Relation::NOT_INTERSECT;
        p = t * p;
        return Relation::INTERSECT;
    }

    Relation ClassifyPoint(const vec3 &p, const AxisAlignedBox &aabb)
    {
        if (p[0] >= aabb.MinPoint()[0] && p[0] <= aabb.MaxPoint()[0] &&
            p[1] >= aabb.MinPoint()[1] && p[1] <= aabb.MaxPoint()[1] &&
            p[2] >= aabb.MinPoint()[2] && p[2] <= aabb.MaxPoint()[2])
            return Relation::INSIDE;
        return Relation::OUTSIDE;
    }


    Relation CrossTriangleAxisAlignedBox(const Triangle3D& t, const AxisAlignedBox& aabb)
    {
        auto pp1 = t[0];
        auto pp2 = t[2];
        auto pp3 = t[3];
        if (pp1[0] > aabb.MaxPoint()[0] && pp2[0] > aabb.MaxPoint()[0] && pp3[0] > aabb.MaxPoint()[0])
            return NOT_INTERSECT;
        if (pp1[0] < aabb.MinPoint()[0] && pp2[0] < aabb.MinPoint()[0] && pp3[0] < aabb.MinPoint()[0])
            return NOT_INTERSECT;
        if (pp1[1] > aabb.MaxPoint()[1] && pp2[1] > aabb.MaxPoint()[1] && pp3[1] > aabb.MaxPoint()[1])
            return NOT_INTERSECT;
        if (pp1[1] < aabb.MinPoint()[1] && pp2[1] < aabb.MinPoint()[1] && pp3[1] < aabb.MinPoint()[1])
            return NOT_INTERSECT;
        if (pp1[2] > aabb.MaxPoint()[2] && pp2[2] > aabb.MaxPoint()[2] && pp3[2] > aabb.MaxPoint()[2])
            return NOT_INTERSECT;
        if (pp1[2] < aabb.MinPoint()[2] && pp2[2] < aabb.MinPoint()[2] && pp3[2] < aabb.MinPoint()[2])
            return NOT_INTERSECT;
        //
        //  the simpliest test
        //
        if (ClassifyPoint(pp1, aabb) == Relation::INSIDE
                || ClassifyPoint(pp2, aabb) == Relation::INSIDE
                || ClassifyPoint(pp3, aabb) == Relation::INSIDE)
            return INTERSECT;

        if (ClipSegment3D(pp1, pp2, aabb.MinPoint(), aabb.MaxPoint()))
            return INTERSECT;
        if (ClipSegment3D(pp2, pp3, aabb.MinPoint(), aabb.MaxPoint()))
            return INTERSECT;
        if (ClipSegment3D(pp3, pp1, aabb.MinPoint(), aabb.MaxPoint()))
            return INTERSECT;

        return NOT_INTERSECT;
    }

    bool ClipSegment(float min, float max, float a, float b, float d, float* t0, float* t1)
    {
        if (fabs(d) < std::numeric_limits<float>().epsilon())
        {
            if (d > 0.0f)
            {
                return !(b < min || a > max);
            }
            else
            {
                return !(a < min || b > max);
            }
        }

        float u0, u1;

        u0 = (min - a) / (d);
        u1 = (max - a) / (d);

        if (u0 > u1)
        {
            float temp = u0;
            u0 = u1;
            u1 = temp;
        }

        if (u1 < *t0 || u0 > *t1)
        {
            return false;
        }

        *t0 = Max(u0, *t0);
        *t1 = Max(u1, *t1);

        if (*t1 < *t0)
        {
            return false;
        }

        return true;
    }

    bool ClipSegment3D(const vec3& A, const vec3& B, const vec3& min, const vec3& max)
    {
        float t0 = 0.0f, t1 = 1.0f;
//		float S[3] = {A[0], A[1], A[2]};
        float D[3] = {B[0]-A[0], B[1]-A[1], B[2]-A[2]};

        if (!ClipSegment(min[0], max[0], A[0], B[0], D[0], &t0, &t1))
        {
            return false;
        }

        if (!ClipSegment(min[1], max[1], A[1], B[1], D[1], &t0, &t1))
        {
            return false;
        }

        if (!ClipSegment(
            min[2], max[2], A[2], B[2], D[2], &t0, &t1))
        {
            return false;
        }

        return true;
    }

    bool ClipSegment2D(const vec2& A, const vec2& B, const vec2& min, const vec2& max)
    {
        float t0 = 0.0f, t1 = 1.0f;
//		float S[2] = {A[0], A[1]};
        float D[2] = {B[0]-A[0], B[1]-A[1]};

        if (!ClipSegment(min[0], max[0], A[0], B[0], D[0], &t0, &t1))
        {
            return false;
        }

        if (!ClipSegment(min[1], max[1], A[1], B[1], D[1], &t0, &t1))
        {
            return false;
        }

        return true;
    }

}

