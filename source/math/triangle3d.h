#ifndef _H_PUNK_MATH_TRIANGLE_3D
#define _H_PUNK_MATH_TRIANGLE_3D

#include "../config.h"
#include "vec3.h"
#include "aabb.h"
#include "relations.h"

namespace Math
{
	class Triangle2D;
	class Line3D;

	class PUNK_ENGINE_PUBLIC Triangle3D
	{
		vec3 m_v[3];
		vec3 m_normal;
		float m_distance;	//	distance from origin
		AxisAlignedBox m_bbox;		
	public:

		Triangle3D();
		Triangle3D(const vec3& v0, const vec3& v1, const vec3& v2);
		const vec3& operator [] (unsigned i) const;
		vec3& operator [] (unsigned i);
		const AxisAlignedBox& GetAxisAlignedBox() const;
		const vec3& GetNormal() const;
		float GetDistance() const { return m_distance; }

		bool GetBarycentric(const vec3& point, float& w0, float& w1, float& w2) const;

		const Triangle2D ProjectXY() const;
		const Triangle2D ProjectXZ() const;
		const Triangle2D ProjectYZ() const;		
	};
	
}

#endif