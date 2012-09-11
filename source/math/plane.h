/*
    File: plane.h
    Author: Nickolai Abramov
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

        Location Classify(const vec3& p) const;
        float Distance(const vec3& p) const;        
		
		void MakeFromPoints(const vec3& a, const vec3& b, const vec3& c);

        Plane Transform(const mat4& matrix) const;

		friend class PUNK_ENGINE Line3D;
    };   
}

#endif
