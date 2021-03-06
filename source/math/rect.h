#ifndef _H_PUNK_MATH_RECT
#define _H_PUNK_MATH_RECT

#include "../config.h"
#include "vec2.h"
#include "vec4.h"

namespace Math
{
	class PUNK_ENGINE Rect
	{
	public:
		Rect();
		Rect(float x, float y, float width, float height);
		Rect(const Math::vec2& left_top_cornder, const Math::vec2 dimension);
		Rect(const Math::vec4& rect);

		float GetX() const { return m_x; }
		float GetY() const { return m_y; }
		float GetWidth() const { return m_width; }
		float GetHeight() const { return m_height; }

	private:

		float m_x;
		float m_y;
		float m_width;
		float m_height;
	};

};

#endif	//	_H_PUNK_MATH_RECT