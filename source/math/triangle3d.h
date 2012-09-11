#ifndef _H_PUNK_MATH_TRIANGLE_3D
#define _H_PUNK_MATH_TRIANGLE_3D

#include "../config.h"
#include "vec3.h"
#include "bounding_box.h"
#include "math_relations.h"

namespace Math
{
	class Triangle2D;
	class Line3D;

	class PUNK_ENGINE Triangle3D
	{
		vec3 m_v[3];
		vec3 m_normal;
		BoundingBox m_bbox;		
	public:

		Triangle3D();
		Triangle3D(const vec3& v0, const vec3& v1, const vec3& v2);
		const vec3& operator [] (unsigned i) const;
		vec3& operator [] (unsigned i);
		const BoundingBox& GetBoundingBox() const;
		const vec3& GetNormal() const;

		const Triangle2D ProjectXY() const;
		const Triangle2D ProjectXZ() const;
		const Triangle2D ProjectYZ() const;

		bool CrossTriangle(const Triangle3D& t);
	};

	PUNK_ENGINE IntersectionType LineCrossTriangle(const Line3D& e, const Triangle3D& p, float& t);
	PUNK_ENGINE Point3DPositionClassification Classify(const vec3& v, const Triangle3D& t);
}

#endif