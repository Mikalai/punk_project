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
    class Line3D;

    class PUNK_ENGINE_API Plane
    {        
    public:

        enum Location {ON, FRONT, BACK};

        Plane();
        Plane(const Plane& plane);
        Plane& operator = (const Plane& plane);

        Plane(const vec3& point, const vec3& normal);
        Plane(const vec3& normal, float distances);
        Plane(const vec3& a, const vec3& b, const vec3& c);
		Plane(float a, float b, float c, float d);
		explicit Plane(const vec4& plane);
        
        Plane& Set(const vec3& normal, float dst);
        Plane& Set(const Line3D& line, const Math::vec3& point);
        Plane& Set(const vec4& value);
        Plane& Set(float a, float b, float c, float d);
        Plane& Set(const vec3& a, const vec3& b, const vec3& c);

        const Plane TransformNode(const mat4& matrix) const;
		const vec3& GetNormal() const;
		float GetDistance() const;
        friend class Line3D;

        Plane& Normalize();

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);

		const vec4& AsVector() const;

        const System::string ToString() const;
	private:

		vec4 m_plane;
    };   

	float operator * (const Plane& plane, const vec3& v);
	float operator * (const Plane& plane, const vec4& v);
	const Plane operator * (const mat4& m, const Plane& p);
}

#endif
