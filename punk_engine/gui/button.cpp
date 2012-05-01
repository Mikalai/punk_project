#include "button.h"
#include "../render/render.h"

namespace GUI
{
	Button::Button(float x, float y, float width, float height, const System::string& text, Widget* parent) 
		: Widget(x,y,width,height,parent)
	{
		m_text = text;
		RenderTextToTexture();
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
}