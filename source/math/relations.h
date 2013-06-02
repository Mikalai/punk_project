#ifndef _H_PUNK_MATH_INTERSECTION_TYPE
#define _H_PUNK_MATH_INTERSECTION_TYPE

#include "../config.h"
#include <vector>

namespace Math
{
	class vec3;
	class vec2;
	class Plane;
	class Line3D;
	class Triangle3D;
	class Sphere;
	class Polygon3D;
	class Ellipsoid;
	class ClipSpace;
	class Portal;
	class BoundingBox;
	class BoundingSphere;
	class ConvexShapeMesh;
	class Rect;
	class Line2D;
	class Frustum;

    enum Relation { INTERSECT,
                    INTERSECT_1 = INTERSECT,
                    INTERSECT_2,
                    INTERSECT_3,
                    INTERSECT_4,
                    NOT_INTERSECT,
                    PARALLEL,
                    SKEW,
                    PERPENDICULAR,
                    INSIDE,
                    OUTSIDE,
                    ON,
                    FRONT,
                    BACK,
                    TOP,
                    BOTTOM,
                    LEFT,
                    RIGHT,
                    START,
                    END,
                    A,
                    B,
                    C,
                    AB,
                    BC,
                    CA,
                    NO_SPLIT_FRONT,
                    NO_SPLIT_BACK,
                    NO_SPLIT_ON,
                    SPLIT_1_FRONT_1_BACK,
                    SPLIT_2_FRONT_1_BACK,
                    SPLIT_1_FRONT_2_BACK,
					VISIBLE, NOT_VISIBLE,
					PARTIALLY_VISIBLE };
		
	PUNK_ENGINE_API Relation ClassifyPoint(const vec3& point, const Line3D& line);
	PUNK_ENGINE_API Relation ClassifyPoint(const vec3& point, const Plane& plane);
	PUNK_ENGINE_API Relation ClassifyPoint(const vec3& point, const Triangle3D& triangle);
	PUNK_ENGINE_API Relation ClassifyPoint(const vec3& point, const ConvexShapeMesh& mesh);
	PUNK_ENGINE_API Relation ClassifyPoint(const vec3& point, const BoundingBox& mesh);
	PUNK_ENGINE_API Relation ClassifyPoint(const vec3& point, const BoundingSphere& mesh);
	PUNK_ENGINE_API Relation ClassifyPoint(const vec3& point, const Frustum& frustum);
	PUNK_ENGINE_API Relation ClassifyPoint(const vec3& point, const ClipSpace& frustum);
	PUNK_ENGINE_API Relation ClassifyPoint(const vec2& point, const Rect& rect);
	
	PUNK_ENGINE_API Relation ClassifyLine(const Line3D& line, const Plane& plane);
	PUNK_ENGINE_API Relation ClassifyLine(const Line3D& line, const Triangle3D& triangle);
	PUNK_ENGINE_API Relation ClassifyLine(const Line3D& line, const ClipSpace& space);
	PUNK_ENGINE_API Relation ClassifyBoudingBox(const BoundingBox& bbox, const ClipSpace& plane);
	PUNK_ENGINE_API Relation ClassifyBoudingSphere(const Sphere& bbox, const ClipSpace& plane);
	

    PUNK_ENGINE_API Relation CrossLineLine(const Line3D& line1, const Line3D& line2, float& t1, float& t2, float& dst);
    PUNK_ENGINE_API Relation CrossLineLine(const Line3D& line1, const Line3D& line2, vec3& p);
    PUNK_ENGINE_API Relation CrossLinePlane(const Line3D& line, const Plane& p, float& t);
	PUNK_ENGINE_API Relation CrossLinePlane(const Line3D& line, const Plane& p, vec3& point);
	PUNK_ENGINE_API Relation CrossLineTriangle(const Line3D& line, const Triangle3D& triangle, float& t);
	PUNK_ENGINE_API Relation CrossLineTriangle(const Line3D& line, const Triangle3D& triangle, vec3& vec);
	PUNK_ENGINE_API Relation CrossLineSphere(const Line3D& line, const Sphere& sphere, float& t1, float& t2);
	PUNK_ENGINE_API Relation CrossLineSphere(const Line3D& line, const Sphere& sphere, vec3& p1, vec3& p2);
	PUNK_ENGINE_API Relation CrossLineEllipsoid(const Line3D& line, const Ellipsoid& ellipsoid, float& t1, float& t2);
	PUNK_ENGINE_API Relation CrossLineEllipsoid(const Line3D& line, const Ellipsoid& ellipsoid, vec3& p1, vec3& p2);
	PUNK_ENGINE_API Relation CrossLineConvexShape(const Line3D& line, const ConvexShapeMesh& shape, float& t1, float& t2, int& face_index1, int& face_index2);
	PUNK_ENGINE_API Relation CrossLineConvexShape(const Line3D& line, const ConvexShapeMesh& shape, vec3& p1, vec3& p2, int& face_index1, int& face_index2);
	PUNK_ENGINE_API Relation CrossSphereSphere(const Sphere& a, const Sphere& b);

	PUNK_ENGINE_API Relation CrossThreePlane(const Plane& a, const Plane& b, const Plane& c, vec3& point);
	PUNK_ENGINE_API Relation CrossPlanePlane(const Plane& a, const Plane& b, Line3D& line);	
	PUNK_ENGINE_API Relation CrossPlaneTriangle(const Plane& plane, const Triangle3D& t, Line3D& line);
	PUNK_ENGINE_API Relation CrossTriangleTriangle(const Triangle3D& a, const Triangle3D& b, Line3D& line);	

	PUNK_ENGINE_API Relation CrossPlanePolygon(const Plane& plane, const Polygon3D& polygon, Polygon3D& front, Polygon3D& back);

	PUNK_ENGINE_API Relation SplitTriangle(const Plane& splitter, const Triangle3D& t, Triangle3D front[2], Triangle3D back[2]);

	PUNK_ENGINE_API Relation ClipPortal(const ClipSpace& clipper, const Portal& portal, Portal& clipped_portal, ClipSpace& reduced_frustum);

	PUNK_ENGINE_API Relation Distance(const Line3D& line1, const Line3D& line2, float& dst, float& t1, float& t2);
    PUNK_ENGINE_API Relation Distance(const Line3D& line, const Math::vec3& point, float& dst);

	//	returns internal part of the line
	PUNK_ENGINE_API Relation ClipExteriorLine(const Line2D& line, const Rect& rect, Line2D& result);
	//	returns external part of the line
	PUNK_ENGINE_API Relation ClipInteriorLine(const Line2D& line, const Rect& rect, Line2D& first, Line2D& second);        

	PUNK_ENGINE_API Relation ClipExteriorLine(const Line3D& line, const Plane& plane, Line3D& ray);

    PUNK_ENGINE_API Relation CrossLines(const std::vector<Line3D>& lines, std::vector<vec3>& points);
	PUNK_ENGINE_API Relation CrossPlanes(const std::vector<Plane>& planes, std::vector<Line3D>& lines);
}

#endif
