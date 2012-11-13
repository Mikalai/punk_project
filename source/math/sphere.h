#ifndef _H_PUNK_MATH_SPHERE
#define _H_PUNK_MATH_SPHERE

#include "../config.h"
#include "vec3.h"

namespace Math
{
	class PUNK_ENGINE Sphere
	{
		vec3 m_center;
		float m_radius;
	public:
		Sphere() : m_center(), m_radius(1) {}
		Sphere(const vec3& center, float radius) : m_center(center), m_radius(radius) {}
		void SetCenter(const vec3& center) { m_center = center; }
		void SetRadius(float radius) { m_radius = radius; }
		void Set(const vec3& center, float radius) { m_center = center; m_radius = radius; }

		float GetRadius() const { return m_radius; }
		const vec3& GetCenter() const { return m_center; }
	};
}

#endif