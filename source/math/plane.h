/*
    File: plane.h
    Author: Mikalaj Abramau
    Desc: Description of geometry 3d plane
*/

#ifndef _H_PUNK_PLANE
#define _H_PUNK_PLANE

#include "../config.h"
#include "vec4.h"
#include "mat4.h"

namespace Math
{    
	class PUNK_ENGINE Line3D;

    class PUNK_ENGINE Plane
    {        
    public:

        enum Location {ON, FRONT, BACK};

        Plane();
        Plane(const Plane& plane);
        Plane& operator = (const Plane& plane);

        Plane(const vec3& point, const vec3& normal);
        Plane(const vec3& normal, float distances);
        Plane(const vec3& a, const vec3& b, const vec3& c);
        
		void Set(const vec3& normal, float dst) { (m_normal = normal, m_distance = dst); }
		void Set(const vec4& value) 
		{ 
			(m_normal = value.XYZ(), m_distance = value.W()); 
			float l = m_normal.Length();
			m_normal.Normalize();
			m_distance /= l;
		}       		

		void Set(const vec3& a, const vec3& b, const vec3& c);

        const Plane TransformNode(const mat4& matrix) const;
		const vec3& GetNormal() const { return m_normal; }
		float GetDistance() const { return m_distance; }
		friend class PUNK_ENGINE Line3D;

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);

	private:

		vec3 m_normal;
        float m_distance;
    };   

	inline float operator * (const Plane& plane, const vec3& v)
	{
		float res = plane.GetNormal().Dot(v) + plane.GetDistance();
		return res;
	}

	inline float operator * (const Plane& plane, const vec4& v)
	{
		float res = plane.GetNormal().Dot(v.XYZ()) + plane.GetDistance()*v.W();
		return res;
	}

	inline const Plane operator * (const mat4& m, const Plane& p)
	{
		const vec4 v(p.GetNormal(), p.GetDistance());
		vec4 t = m * v;
		Plane res(t.XYZ(), t.W());
		return res;
	}
}

#endif
