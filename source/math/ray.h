#ifndef _H_PUNK_MATH_RAY
#define _H_PUNK_MATH_RAY

#include "../config.h"
#include "vec3.h"

namespace Math
{
	class PUNK_ENGINE Ray
	{
		vec3 m_start;
		vec3 m_dir;
	public:
		Ray();
		Ray(const vec3& start, const vec3 dir);
	};

	
}

#endif