#ifndef _H_PUNK_MATH_SPHERE
#define _H_PUNK_MATH_SPHERE

#include "../config.h"
#include "vec3.h"
#include "mat4.h"

namespace Math
{
	class PUNK_ENGINE_API Sphere
	{		
	public:
		Sphere() : m_center(), m_radius(0) {}
		Sphere(const vec3& center, float radius) : m_center(center), m_radius(radius) {}
		void SetCenter(const vec3& center) { m_center = center; }
		void SetRadius(float radius) { m_radius = radius; }
		void Set(const vec3& center, float radius) { m_center = center; m_radius = radius; }

		float GetRadius() const { return m_radius; }
		const vec3& GetCenter() const { return m_center; }

	private:
		vec3 m_center;
		float m_radius;

        friend const Sphere operator * (const mat4& m, const Sphere& s);
        friend void SaveSphere(System::Buffer* buffer, const Sphere& value);
        friend void LoadSphere(System::Buffer* buffer, Sphere& value);
	};

    PUNK_ENGINE_API const Sphere operator * (const mat4& m, const Sphere& s);
    PUNK_ENGINE_API const Sphere operator + (const Sphere& a, const Sphere& b);
    PUNK_ENGINE_API void SaveSphere(System::Buffer* buffer, const Sphere& value);
    PUNK_ENGINE_API void LoadSphere(System::Buffer* buffer, Sphere& value);
}

#endif
