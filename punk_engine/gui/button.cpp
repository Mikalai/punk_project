#include "button.h"
#include "../render/render.h"

namespace GUI
{
	Button::Button(float x, float y, float width, float height, const System::string& text) : Widget(x,y,width,height)
	{
		m_text = text;
		RenderTextToTexture();
	}

	void Button::Render()
	{
/*		Render::QuadRender::Parameters* p1 = Render::QuadRender::Parameters::Create();
		p1->m_x = (float)GetX();
		p1->m_y = (float)GetY();
		p1->m_width = (float)m_width;
		p1->m_height = (float)m_height;
		p1->m_back_color[0] = m_back_color[0]; p1->m_back_color[1] = m_back_color[1]; p1->m_back_color[2] = m_back_color[2]; p1->m_back_color[3] = m_back_color[3];
		Render::RenderPipeline::GetRenderPipeline()->Add(m_quadRender, (void*)p1);		

		Render::TextAreaRender::Parameters* p2 = Render::TextAreaRender::Parameters::Create();
		p2->m_back_color[0] = m_text_color[0]; p2->m_back_color[1] = m_text_color[1]; p2->m_back_color[2] = m_text_color[2]; p2->m_back_color[3] = m_text_color[3];
		p2->m_x = (float)GetX();
		p2->m_y = (float)GetY();
		p2->m_width = (float)m_width;
		p2->m_height = (float)m_height;
		p2->m_texture = &m_textTexture;
		Render::RenderPipeline::GetRenderPipeline()->Add(m_textRender, (void*)p2);*/
	}

	Button::~Button()
	{
	}

	void Button::OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* e)
	{
		Widget::OnMouseLeftButtonDown(e);
	}

	void Button::OnIdle(System::IdleEvent* e)
	{
		Widget::OnIdle(e);
		if (m_isCursorIn)
		{
			if (m_leftButtonDown)
			{				
				m_back_color = Math::vec4(1,1,1,1);
				m_text_color = Math::vec4(0,0,0,1);
			}			
			else
			{
				m_animation = min(m_animation, m_animation_duration);
				m_back_color = Math::linear_interpolation(m_back_color_0, m_back_color_1, m_animation / m_animation_duration);
				m_text_color = Math::linear_interpolation(m_text_color_0, m_text_color_1, m_animation / m_animation_duration);
			}
		}
	}

	bool Button::EventHandler(System::Event* event)
	{	
		switch (event->eventCode)
		{
		case System::EVENT_IDLE:

		default:
			Widget::EventHandler(event);
		}
		return false;
	}
}