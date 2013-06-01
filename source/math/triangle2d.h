#ifndef _H_PUNK_MATH_TRIANGLE_2D
#define _H_PUNK_MATH_TRIANGLE_2D

#include "../config.h"
#include "vec2.h"

namespace Math
{
	class PUNK_ENGINE_PUBLIC Triangle2D
    {
        vec2 a;
        vec2 b;
        vec2 c;
	public:
        Triangle2D();
        Triangle2D(const vec2& v0, const vec2& v1, const vec2& v2);        
		bool IsPointIn(const vec2& p) const;
    };
}

#endif