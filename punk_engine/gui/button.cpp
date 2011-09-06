#include "../system/allocator.h"
#include "button.h"
#include "../render/render.h"

namespace GUI
{
	Button::Button(int x, int y, int width, int height, const System::string& text, Widget* parent) : Widget(x,y,width,height,parent)
	{
		m_text = text;
		m_quadRender = Render::QuadRender::GetRender();
		m_textRender = Render::TextAreaRender::GetRender();	
		RenderTextToTexture();
	}

	void Button::Render()
	{
		Render::QuadRender::Parameters* p1 = Render::QuadRender::Parameters::Create();
		p1->m_x = (float)GetX();
		p1->m_y = (float)GetY();
		p1->m_width = (float)m_width;
		p1->m_height = (float)m_height;
		p1->m_color[0] = m_color[0]; p1->m_color[1] = m_color[1]; p1->m_color[2] = m_color[2]; p1->m_color[3] = m_color[3];
		Render::RenderPipeline::GetRenderPipeline()->Add(m_quadRender, (void*)p1);		

		Render::TextAreaRender::Parameters* p2 = Render::TextAreaRender::Parameters::Create();
		p2->m_color[0] = m_textColor[0]; p2->m_color[1] = m_textColor[1]; p2->m_color[2] = m_textColor[2]; p2->m_color[3] = m_textColor[3];
		p2->m_x = (float)GetX();
		p2->m_y = (float)GetY();
		p2->m_width = (float)m_width;
		p2->m_height = (float)m_height;
		p2->m_texture = &m_textTexture;
		Render::RenderPipeline::GetRenderPipeline()->Add(m_textRender, (void*)p2);
	}

	Button::~Button()
	{
	}

	bool Button::EventHandler(System::Event* event)
	{	
		switch (event->eventCode)
		{
		case System::EVENT_IDLE:
			if (m_isCursorIn)
			{
				if (m_leftButtonDown)
				{
					m_color[0] += (1 - m_activeColor[0] - m_color[0]) / 2.0f;
					m_color[1] += (1 - m_activeColor[1] - m_color[1]) / 2.0f;
					m_color[2] += (1 - m_activeColor[2] - m_color[2]) / 2.0f;
					m_color[3] += (m_activeColor[3] - m_color[3]) / 2.0f;

					m_textColor[0] += (1 - m_textActiveColor[0] - m_textColor[0]) / 2.0f;
					m_textColor[1] += (1 - m_textActiveColor[1] - m_textColor[1]) / 2.0f;
					m_textColor[2] += (1 - m_textActiveColor[2] - m_textColor[2]) / 2.0f;
					m_textColor[3] += (m_textActiveColor[3] - m_textColor[3]) / 2.0f;
				}			
				else
				{
					m_color[0] += (m_activeColor[0] - m_color[0]) / 10.0f;
					m_color[1] += (m_activeColor[1] - m_color[1]) / 10.0f;
					m_color[2] += (m_activeColor[2] - m_color[2]) / 10.0f;
					m_color[3] += (m_activeColor[3] - m_color[3]) / 10.0f;

					m_textColor[0] += (m_textActiveColor[0] - m_textColor[0]) / 10.0f;
					m_textColor[1] += (m_textActiveColor[1] - m_textColor[1]) / 10.0f;
					m_textColor[2] += (m_textActiveColor[2] - m_textColor[2]) / 10.0f;
					m_textColor[3] += (m_textActiveColor[3] - m_textColor[3]) / 10.0f;
				}
			}
			else
			{
				m_color[0] += (m_inactiveColor[0] - m_color[0]) / 10.0f;
				m_color[1] += (m_inactiveColor[1] - m_color[1]) / 10.0f;
				m_color[2] += (m_inactiveColor[2] - m_color[2]) / 10.0f;
				m_color[3] += (m_inactiveColor[3] - m_color[3]) / 10.0f;	

				m_textColor[0] += (m_textInactiveColor[0] - m_textColor[0]) / 10.0f;
				m_textColor[1] += (m_textInactiveColor[1] - m_textColor[1]) / 10.0f;
				m_textColor[2] += (m_textInactiveColor[2] - m_textColor[2]) / 10.0f;
				m_textColor[3] += (m_textInactiveColor[3] - m_textColor[3]) / 10.0f;
			}
			break;
		default:
			Widget::EventHandler(event);
		}
		return false;
	}
}