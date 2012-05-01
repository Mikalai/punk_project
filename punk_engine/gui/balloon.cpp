#include "balloon.h"
#include "gui_render.h"

namespace GUI
{
	Balloon::Balloon(float x, float y, float w, float h, const System::string& m, Widget* p)
		: Widget(x, y, w, h, p)
		, m_show_time(3)
		, m_appear_time(0.1)
		, m_disappear_time(0.1)
		, m_scale(1)
	{
		m_text = m;
		RenderTextToTexture();
		m_isVisible = false;
	}

	void Balloon::Blink()
	{
		m_isVisible = true;
		m_cur_time = 0;
		m_back_color_0[3] = 0;
		m_back_color_1[3] = 1;
		m_text_color_0[3] = 0;
		m_text_color_0[3] = 1;
		m_scale = 0;
	}

	float Balloon::GetScale() const
	{
		return m_scale;
	}

	void Balloon::SetShowTime(float value)
	{
		m_show_time = value;
	}

	float Balloon::GetShowTime() const
	{
		return m_show_time;
	}

	void Balloon::SetAppearTime(float v)
	{
		m_appear_time = v;
	}

	float Balloon::GetAppearTime() const
	{
		return m_appear_time;
	}
	
	void Balloon::SetDisappearTime(float v)
	{
		m_disappear_time = v;
	}

	float Balloon::GetDisappearTime() const
	{
		return m_disappear_time;
	}
	
	void Balloon::OnIdle(System::IdleEvent* e)
	{	
		if (m_isVisible && m_isEnabled)
		{
			Widget::OnIdle(e);
			m_cur_time += e->elapsed_time_s;
			float t = m_cur_time;
			if (t < m_appear_time)
			{
				m_back_color[3] = m_scale = t / m_appear_time;				
			}
			else if (t < m_appear_time + m_show_time)
			{
				m_back_color[3] = m_scale = 1;
			}
			else if (t < m_appear_time + m_show_time + m_disappear_time)
			{
				t -= m_appear_time + m_show_time;
				m_back_color[3] = m_scale = 1 - t / m_disappear_time;
			}
			else
			{
				m_isVisible = false;
			}
		}
	}

	void Balloon::Render(IGUIRender* render) const
	{
		if (m_isVisible)
			render->RenderBalloon(this);
	}

	Balloon::~Balloon()
	{
	}
}