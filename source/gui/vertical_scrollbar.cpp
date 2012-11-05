#include "vertical_scrollbar.h"
#include "gui_render.h"

namespace GUI
{
	static const float g_auto_scroll = 0.5;

	VerticalScrollBar::VerticalScrollBar(float x, float y, float width, float height, Widget* parent) 
		: Widget(x, y, width, height, L"", parent)
		, m_timer(0)
	{
		m_slider = new VerticalSlider(0, 0.05f, 1, 0.90f, 0, 100, this);
		m_upButton = new Button(0, 0.95f, 1, 0.05f, L"", this);
		m_upButton->SetMouseLeftClickHandler(System::EventHandler(this, &VerticalScrollBar::OnUpButtonLeftClick));
		m_downButton = new Button(0, 0, 1, 0.05f, L"", this);
		m_downButton->SetMouseLeftClickHandler(System::EventHandler(this, &VerticalScrollBar::OnDownButtonLeftClick));
	}

	VerticalScrollBar::~VerticalScrollBar()
	{
	}

	void VerticalScrollBar::OnIdle(System::IdleEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			Widget::OnIdle(e);
		}
	}

	void VerticalScrollBar::Render(IGUIRender* render) const
	{
		if (IsVisible())
		{
			render->RenderVerticalSlider(m_slider);
			render->RenderWidget(m_upButton);
			render->RenderWidget(m_downButton);
		}
	}

	void VerticalScrollBar::OnDownButtonLeftClick(System::Event*)
	{
		if (IsVisible() && IsEnabled())
		{
			m_slider->SetCurrent(m_slider->GetCurrent() + 1);		
		}
	}

	void VerticalScrollBar::OnUpButtonLeftClick(System::Event*)
	{
		if (IsVisible() && IsEnabled())
		{
			m_slider->SetCurrent(m_slider->GetCurrent() - 1);
		}
	}

	int VerticalScrollBar::GetCurrent() const
	{
		return m_slider->GetCurrent();
	}

	void VerticalScrollBar::SetCurrent(int value)
	{
		m_slider->SetCurrent(value);
	}

	void VerticalScrollBar::SetMax(int Max)
	{
		m_slider->SetBounds(0, Max);
	}

	void VerticalScrollBar::OnChangeValue(System::Handler handler)
	{
		if (IsVisible() && IsEnabled())
		{
			m_slider->OnChangeValue(handler);
		}
	}

}