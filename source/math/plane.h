/*
    File: plane.h
    Author: Mikalaj Abramau
    Desc: Description of geometry 3d plane
*/

#ifndef _H_PUNK_PLANE
#define _H_PUNK_PLANE

#include "../config.h"
#include "vec3.h"
#include "mat4.h"

namespace Math
{    
	class PUNK_ENGINE Line3D;

    class PUNK_ENGINE Plane
    {        
        vec3 normal;
        float distance;
    public:

        enum Location {ON, FRONT, BACK};

        Plane();
        Plane(const Plane& plane);
        Plane& operator = (const Plane& plane);

        Plane(const vec3& point, const vec3& normal);
        Plane(const vec3& normal, float distances);
        Plane(const vec3& a, const vec3& b, const vec3& c);
        
       		
		void MakeFromPoints(const vec3& a, const vec3& b, const vec3& c);

        Plane Transform(const mat4& matrix) const;
		const vec3& GetNormal() const { return normal; }
		float GetDistance() const { return distance; }
		friend class PUNK_ENGINE Line3D;
    };   
}

#endif
