#ifndef _H_PUNK_MATH_INTERSECTION_TYPE
#define _H_PUNK_MATH_INTERSECTION_TYPE

#include "../config.h"

namespace Math
{
	class vec3;
	class Plane;
	class Line3D;
	class Triangle3D;

	enum Relation { INTERSECT, NOT_INTERSECT, PARALLEL, SKEW, PERPENDICULAR, INSIDE, OUTSIDE, ON, FRONT, BACK, TOP, BOTTOM, LEFT, RIGHT, START, END, A, B, C, AB, BC, CA};

	PUNK_ENGINE Relation ClassifyPoint(const vec3& point, const Line3D& line);
	PUNK_ENGINE Relation ClassifyPoint(const vec3& point, const Plane& plane);
	PUNK_ENGINE Relation ClassifyPoint(const vec3& point, const Triangle3D& triangle);
	PUNK_ENGINE Relation ClassifyLine(const Line3D& line, const Plane& plane);
	PUNK_ENGINE Relation ClassifyLine(const Line3D& line, const Triangle3D& triangle);	

	PUNK_ENGINE Relation CrossLinePlane(const Line3D& line, const Plane& plane, vec3& t);		
	PUNK_ENGINE Relation CrossLinePlane(const Line3D& line, const Plane& p, vec3& point);
	PUNK_ENGINE Relation CrossLineTriangle(const Line3D& line, const Triangle3D& triangle, float& t);
	PUNK_ENGINE Relation CrossLineTriangle(const Line3D& line, const Triangle3D& triangle, vec3& vec);
	PUNK_ENGINE Relation CrossThreePlane(const Plane& a, const Plane& b, const Plane& c, vec3& point);
	PUNK_ENGINE Relation CrossPlanePlane(const Plane& a, const Plane& b, Line3D& line);	
	PUNK_ENGINE Relation CrossTriangleTriangle(const Triangle3D& a, const Triangle3D& b, Line3D& line);	
	
}

#endif