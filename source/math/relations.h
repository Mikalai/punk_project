#ifndef _H_PUNK_MATH_INTERSECTION_TYPE
#define _H_PUNK_MATH_INTERSECTION_TYPE

#include "../config.h"

namespace Math
{
	class vec3;
	class Plane;
	class Line3D;
	class Triangle3D;
	class Sphere;
	class Polygon3D;

	enum Relation { INTERSECT, INTERSECT_1 = INTERSECT, INTERSECT_2, INTERSECT_3, INTERSECT_4, NOT_INTERSECT, PARALLEL, SKEW, PERPENDICULAR, INSIDE, OUTSIDE, ON, FRONT, BACK, TOP, BOTTOM, LEFT, RIGHT, START, END, A, B, C, AB, BC, CA, NO_SPLIT_FRONT, NO_SPLIT_BACK, NO_SPLIT_ON, SPLIT_1_FRONT_1_BACK, SPLIT_2_FRONT_1_BACK, SPLIT_1_FRONT_2_BACK };

	PUNK_ENGINE Relation ClassifyPoint(const vec3& point, const Line3D& line);
	PUNK_ENGINE Relation ClassifyPoint(const vec3& point, const Plane& plane);
	PUNK_ENGINE Relation ClassifyPoint(const vec3& point, const Triangle3D& triangle);
	PUNK_ENGINE Relation ClassifyLine(const Line3D& line, const Plane& plane);
	PUNK_ENGINE Relation ClassifyLine(const Line3D& line, const Triangle3D& triangle);	

	PUNK_ENGINE Relation CrossLinePlane(const Line3D& line, const Plane& plane, vec3& t);		
	PUNK_ENGINE Relation CrossLinePlane(const Line3D& line, const Plane& p, vec3& point);
	PUNK_ENGINE Relation CrossLineTriangle(const Line3D& line, const Triangle3D& triangle, float& t);
	PUNK_ENGINE Relation CrossLineTriangle(const Line3D& line, const Triangle3D& triangle, vec3& vec);
	PUNK_ENGINE Relation CrossLineSphere(const Line3D& line, const Sphere& sphere, float& t1, float& t2);
	PUNK_ENGINE Relation CrossLineSphere(const Line3D& line, const Sphere& sphere, vec3& p1, vec3& p2);

	PUNK_ENGINE Relation CrossThreePlane(const Plane& a, const Plane& b, const Plane& c, vec3& point);
	PUNK_ENGINE Relation CrossPlanePlane(const Plane& a, const Plane& b, Line3D& line);	
	PUNK_ENGINE Relation CrossPlaneTriangle(const Plane& plane, const Triangle3D& t, Line3D& line);
	PUNK_ENGINE Relation CrossTriangleTriangle(const Triangle3D& a, const Triangle3D& b, Line3D& line);	

	PUNK_ENGINE Relation CrossPlanePolygon(const Plane& plane, const Polygon3D& polygon, Polygon3D& front, Polygon3D& back);

	PUNK_ENGINE Relation SplitTriangle(const Plane& splitter, const Triangle3D& t, Triangle3D front[2], Triangle3D back[2]);
}

#endif