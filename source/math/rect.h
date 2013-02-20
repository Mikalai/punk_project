#ifndef _H_PUNK_MATH_RECT
#define _H_PUNK_MATH_RECT

#include "vec2.h"
#include "vec4.h"

namespace Math
{
	class Rect
	{
	public:
		Rect();
		Rect(float x, float y, float width, float height);
		Rect(const Math::vec2& left_top_cornder, const Math::vec2 dimension);
		Rect(const Math::vec4& rect);

	private:

	};

};

#endif	//	_H_PUNK_MATH_RECT