#ifndef _H_PUNK_MATH_RECT
#define _H_PUNK_MATH_RECT

#include "../config.h"
#include "vec2.h"
#include "vec4.h"

namespace Math
{
	class PUNK_ENGINE_API Rect
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

		void Set(float x, float y, float width, float height);
		
	private:

		float m_x;
		float m_y;
		float m_width;
		float m_height;
	};

	inline void Rect::Set(float x, float y, float width, float height)
	{
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
	}
};

#endif	//	_H_PUNK_MATH_RECT