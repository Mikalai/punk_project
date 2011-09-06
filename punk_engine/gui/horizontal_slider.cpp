#include "horizontal_slider.h"

namespace GUI
{
	HorizontalSlider::HorizontalSlider(int x, int y, int width, int height, int min, int max, Widget* parent) :
		Widget(x,y,width,height, parent), m_min(min), m_max(max), m_cur(0), m_prev(0)
	{
		m_quadRender = Render::QuadRender::GetRender();
		m_textRender = Render::TextAreaRender::GetRender();
	}

	HorizontalSlider::~HorizontalSlider()
	{
	}

	void HorizontalSlider::SetMin(int min)
	{
		m_min = min;
	}

	void HorizontalSlider::SetMax(int max)
	{
		m_max = max;
	}

	void HorizontalSlider::SetCurrent(int cur)
	{
		m_cur = cur;
	}

	int HorizontalSlider::GetMin() const
	{
		return m_min;
	}

	int HorizontalSlider::GetMax() const
	{
		return m_max;
	}

	int HorizontalSlider::GetCurrent() const
	{
		return m_cur;
	}

	void HorizontalSlider::Render()
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
		p3->m_height = (float)m_height;
		p3->m_width = 20.0f;
		p3->m_x = float(-10 + GetX() + m_cur * m_width / (m_max - m_min));
		p3->m_y = float(GetY());
		Render::RenderPipeline::GetRenderPipeline()->Add(m_quadRender, (void*)p3);
	}

	bool HorizontalSlider::EventHandler(System::Event* event)
	{
		Widget::EventHandler(event);

		switch(event->eventCode)
		{
		case System::EVENT_IDLE:
			if (m_prev != m_cur)
			{
				event->anyData = (void*)m_cur;
				m_onChangeValue(event);
			}
			break;
		case System::EVENT_MOUSE_LBUTTON_DOWN:
			{
				System::MouseLeftButtonDownEvent* e = static_cast<System::MouseLeftButtonDownEvent*>(event);
				m_cur = (e->x - GetX()) / (float)m_width * (float)(m_max - m_min) + 1;
			}
			break;
		case System::EVENT_MOUSE_MOVE:
			{
				System::MouseMoveEvent* e = static_cast<System::MouseMoveEvent*>(event);
				if (m_isCursorIn)
				{
					if (m_leftButtonDown)
					{
						m_cur = (e->x - GetX()) / (float)m_width * (float)(m_max - m_min) + 1;
					}
				}
			}
		}
		return false;
	}
}