#include "vertical_slider.h"
#include "gui_render.h"

namespace GUI
{
	VerticalSlider::VerticalSlider(float x, float y, float width, float height, int Min, int Max, Widget* parent) 
		: Widget(x, y, width, height, L"", parent), m_min(Min), m_max(Max), m_cur(0), m_prev(0)
	{
		m_text = "Vertical Slider";
	}

	VerticalSlider::~VerticalSlider()
	{
	}

	void VerticalSlider::SetMin(int Min)
	{
		m_min = Min;
	}

	void VerticalSlider::SetMax(int Max)
	{
		m_max = Max;
	}

	void VerticalSlider::SetCurrent(int cur)
	{
		if ((cur <= m_max) && (cur >= m_min))
			m_cur = cur;
	}

	int VerticalSlider::GetMin() const
	{
		return m_min;
	}

	int VerticalSlider::GetMax() const
	{
		return m_max;
	}

	int VerticalSlider::GetCurrent() const
	{
		return m_cur;
	}

	void VerticalSlider::SetBounds(int Min, int Max)
	{
		m_min = Min;
		m_max = Max;
	}

	void VerticalSlider::OnChangeValue(System::Handler handler)
	{
		if (IsVisible() && IsEnabled())
		{
			m_onChangeValue = handler;
		}
	}

	void VerticalSlider::Render(IGUIRender* render) const
	{
		if (IsVisible())
			render->RenderVerticalSlider(this);
	}

	void VerticalSlider::OnIdle(System::IdleEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			if (m_prev != m_cur)
			{
				e->anyData = (void*)m_cur;
				m_onChangeValue(e);
				m_prev = m_cur;
			}
			Widget::OnIdle(e);
		}
	}

	void VerticalSlider::OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			if (m_isCursorIn)
			{
				Math::vec2 p = Widget::WindowToViewport(e->x, e->y);
				m_cur = m_max - int((p.Y() - GetY() / (float)GetHeight() * (float)(m_max - m_min) + 1));
				//SendChildren(e);
				Widget::OnMouseLeftButtonDown(e);
			}
			Widget::OnMouseLeftButtonDown(e);
		}
	}

	void VerticalSlider::OnMouseWheel(System::MouseWheelEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			if (m_isCursorIn)
			{
				m_cur -= e->delta;
				if (m_cur < m_min)
					m_cur = m_min;
				if (m_cur > m_max)
					m_cur = m_max;
			}
			Widget::OnMouseWheel(e);
		}
	}

	void VerticalSlider::OnMouseMove(System::MouseMoveEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			if (m_leftButtonDown)
			{
				Math::vec2 p = Widget::WindowToViewport(e->x, e->y);
				m_cur = m_max - int((p.Y() - GetY() / (float)GetHeight() * (float)(m_max - m_min) + 1));
			}
			Widget::OnMouseMove(e);
		}
	}
}
