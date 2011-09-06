#include "vertical_slider.h"

namespace GUI
{
	VerticalSlider::VerticalSlider(int x, int y, int width, int height, int min, int max, Widget* parent) :
		Widget(x,y,width,height, parent), m_min(min), m_max(max), m_cur(0), m_prev(0)
	{
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

	void VerticalSlider::Render()
	{
		Render::QuadRender::Parameters* p1 = Render::QuadRender::Parameters::Create();
		p1->m_color[0] = m_color[0]; p1->m_color[1] = m_color[1]; p1->m_color[2] = m_color[2]; p1->m_color[3] = m_color[3];
		p1->m_height = (float)m_height;
		p1->m_width = (float)m_width;
		p1->m_x = (float)GetX();
		p1->m_y = (float)GetY();
		Render::RenderPipeline::GetRenderPipeline()->Add(m_quadRender, (void*)p1);

		Render::QuadRender::Parameters* p3 = Render::QuadRender::Parameters::Create();
		p3->m_color[0] =  1 - m_color[0]; p3->m_color[1] = 1 - m_color[1]; p3->m_color[2] = 1 - m_color[2]; p3->m_color[3] = m_color[3];
		p3->m_height = 20.0;
		p3->m_width = (float)m_width;
		p3->m_x = (float)GetX();
		p3->m_y = float(-10 + GetY() + (m_max - m_cur) * m_height / (m_max - m_min));
		Render::RenderPipeline::GetRenderPipeline()->Add(m_quadRender, (void*)p3);
	}

	bool VerticalSlider::EventHandler(System::Event* event)
	{	
		switch(event->eventCode)
		{
		case System::EVENT_IDLE:
			if (m_prev != m_cur)
			{
				event->anyData = (void*)m_cur;
				m_onChangeValue(event);
				m_prev = m_cur;
			}
			Widget::EventHandler(event);
			break;
		case System::EVENT_MOUSE_LBUTTON_DOWN:
			{
				System::MouseLeftButtonDownEvent* e = static_cast<System::MouseLeftButtonDownEvent*>(event);
				m_cur = m_max - int((e->y - GetY()) / (float)m_height * (float)(m_max - m_min) + 1);
				SendChildren(event);
				Widget::EventHandler(event);
			}
			break;
		case System::EVENT_MOUSE_MOVE:
			{
				System::MouseMoveEvent* e = static_cast<System::MouseMoveEvent*>(event);
				if (m_leftButtonDown)
				{
					m_cur = m_max - int((e->y - GetY()) / (float)m_height * (float)(m_max - m_min) + 1);
				}
				SendChildren(event);
			}
		default:
			Widget::EventHandler(event);
		}
		return false;
	}
}