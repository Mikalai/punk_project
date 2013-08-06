#ifndef _H_PUNK_MATH_LINE_2D
#define _H_PUNK_MATH_LINE_2D

#include "../config.h"
#include "vec2.h"
#include "relations.h"

namespace Math
{
    class PUNK_ENGINE_API Line2D
    {
        vec2 m_origin;
        vec2 m_destination;
	public:
        Line2D();
		Line2D(const vec2& org, const vec2& dest);
        Line2D(const Line2D& line);
        Line2D& Rotate();
        Line2D& Flip();
        const vec2 Direction() const;
        float SegmentLength() const;
        const vec2& Origin() const;
		vec2& Origin();
        const vec2& Destination() const;
		vec2& Destination();
		Relation CrossLine(const Line2D& line, float& t);
        const vec2 Point(float t);
    };

	float Distance(const vec2& p, const Line2D& line);
}
#endif