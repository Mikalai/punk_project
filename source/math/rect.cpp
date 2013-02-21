#include "rect.h"

namespace Math
{
	Rect::Rect()
		: m_x(0)
		, m_y(0)
		, m_width(1)
		, m_height(1)
	{}

	Rect::Rect(float x, float y, float width, float height)
		: m_x(x)
		, m_y(y)
		, m_width(width)
		, m_height(height)
	{}

	Rect::Rect(const Math::vec2& left_top_cornder, const Math::vec2 dimension)
		: m_x(left_top_cornder.X())
		, m_y(left_top_cornder.Y())
		, m_width(dimension.X())
		, m_height(dimension.Y())
	{}

	Rect::Rect(const Math::vec4& rect)
		: m_x(rect.X())
		, m_y(rect.Y())
		, m_width(rect.Z())
		, m_height(rect.W())
	{}
}
