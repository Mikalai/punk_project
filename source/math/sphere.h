#ifndef _H_PUNK_MATH_SPHERE
#define _H_PUNK_MATH_SPHERE

#include "../config.h"
#include "vec3.h"
#include "mat4.h"

namespace Math
{
	class PUNK_ENGINE_PUBLIC Sphere
	{		
	public:
		Sphere() : m_center(), m_radius(0) {}
		Sphere(const vec3& center, float radius) : m_center(center), m_radius(radius) {}
		void SetCenter(const vec3& center) { m_center = center; }
		void SetRadius(float radius) { m_radius = radius; }
		void Set(const vec3& center, float radius) { m_center = center; m_radius = radius; }

		float GetRadius() const { return m_radius; }
		const vec3& GetCenter() const { return m_center; }

		friend const Sphere operator * (const mat4& m, const Sphere& s);

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);
		
	private:
		vec3 m_center;
		float m_radius;
	};

	inline const Sphere operator * (const mat4& m, const Sphere& s)
	{
		Sphere res;
		res.m_center = m * s.GetCenter();
		//	consider that transform do not effect the radius
		res.m_radius = s.GetRadius();
		return res;
	}

	inline const Sphere operator + (const Sphere& a, const Sphere& b)
	{
		float d = (a.GetCenter() - b.GetCenter()).Length();
		if (d + a.GetRadius() <= b.GetRadius())
			return b;
		if (d + b.GetRadius() <= a.GetRadius())
			return a;

		Sphere res;		
		float r = 0.5f * (d + a.GetRadius() + b.GetRadius());
		res.SetRadius(r);
		res.SetCenter(a.GetCenter() + (r - a.GetRadius()) / d * (b.GetCenter() - a.GetCenter()));
		return res;
	}
}

#endif