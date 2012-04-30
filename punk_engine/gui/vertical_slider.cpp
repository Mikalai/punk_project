#include "vertical_slider.h"
#include "gui_render.h"

namespace GUI
{
	VerticalSlider::VerticalSlider(float x, float y, float width, float height, int min, int max, Widget* parent) :
		Widget(x, y, width, height, parent), m_min(min), m_max(max), m_cur(0), m_prev(0)
	{
		m_text = "Vertical Slider";
	}

	VerticalSlider::~VerticalSlider()
	{
	}

	void VerticalSlider::SetMin(int min)
	{
		m_min = min;
	}

	void VerticalSlider::SetMax(int max)
	{
		m_max = max;
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

	void VerticalSlider::SetBounds(int min, int max)
	{
		m_min = min;
		m_max = max;
	}

	void VerticalSlider::OnChangeValue(System::Handler handler)
	{
		m_onChangeValue = handler;
	}

	void VerticalSlider::Render(IGUIRender* render) const
	{
		render->RenderVerticalSlider(this);
	}

	void VerticalSlider::OnIdle(System::IdleEvent* e)
	{
		if (m_prev != m_cur)
		{
			e->anyData = (void*)m_cur;
			m_onChangeValue(e);
			m_prev = m_cur;
		}
		Widget::OnIdle(e);
	}

	void VerticalSlider::OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* e)
	{
		Math::vec2 p = Widget::WindowToViewport(e->x, e->y);
		m_cur = m_max - int((p.Y() - GetY()) / (float)GetHeight() * (float)(m_max - m_min) + 1);
		//SendChildren(e);
		Widget::OnMouseLeftButtonDown(e);
	}

	void VerticalSlider::OnMouseMove(System::MouseMoveEvent* e)
	{
		if (m_leftButtonDown)
		{
			Math::vec2 p = Widget::WindowToViewport(e->x, e->y);
			m_cur = m_max - int((p.Y() - GetY()) / (float)m_height * (float)(m_max - m_min) + 1);
		}
		Widget::OnMouseMove(e);
	}
}
