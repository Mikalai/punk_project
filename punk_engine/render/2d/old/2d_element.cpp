#include "2d_element.h"

namespace Render
{
	namespace _2D
	{
		_2DRenderElement::_2DRenderElement() : m_x(0), m_y(0), m_width(0), m_height(0)
		{
			m_color[0] = m_color[1] = m_color[2] = m_color[3] = 0;
		}

		_2DRenderElement::_2DRenderElement(int x, int y, int width, int height) : m_x(x), m_y(y), m_width(width), m_height(height)
		{
			m_color[0] = m_color[1] = m_color[2] = m_color[3] = 0;
		}

		void _2DRenderElement::SetSize(int x, int y, int width, int height)
		{
			m_x = x;
			m_y = y;
			m_width = width;
			m_height = height;
		}

		void _2DRenderElement::SetColor(float r, float g, float b, float a)
		{
			m_color[0] = r;
			m_color[1] = g;
			m_color[2] = b;
			m_color[3] = a;
		}
	}
}