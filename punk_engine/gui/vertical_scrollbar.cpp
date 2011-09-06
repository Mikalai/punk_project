#include "vertical_scrollbar.h"
#include "../render/render.h"

namespace GUI
{
	VerticalScrollBar::VerticalScrollBar(int x, int y, int width, int height, Widget* parent) : 
		Widget(x, y, width, height, parent)
	{
		m_slider = new VerticalSlider(0, 20, width, height - 40, 0, 1, this);
		m_upButton = new Button(0, height - 20, width, 20, L"", this);
		m_upButton->OnLeftClick(System::EventHandler(this, &VerticalScrollBar::OnUpButtonLeftClick));
		m_downButton = new Button(0, 0, width, 20, L"", this);
		m_downButton->OnLeftClick(System::EventHandler(this, &VerticalScrollBar::OnDownButtonLeftClick));
	}

	VerticalScrollBar::~VerticalScrollBar()
	{
	}

	void VerticalScrollBar::Render()
	{
		m_slider->Render();
		m_upButton->Render();
		m_downButton->Render();
	}

	void VerticalScrollBar::OnDownButtonLeftClick(System::Event*)
	{
		m_slider->SetCurrent(m_slider->GetCurrent() + 1);
	}

	void VerticalScrollBar::OnUpButtonLeftClick(System::Event*)
	{
		m_slider->SetCurrent(m_slider->GetCurrent() - 1);
	}

	int VerticalScrollBar::GetCurrent() const
	{
		return m_slider->GetCurrent();
	}

	void VerticalScrollBar::SetCurrent(int value)
	{
		m_slider->SetCurrent(value);
	}

	void VerticalScrollBar::SetMax(int max)
	{
		m_slider->SetBounds(0, max);
	}
	
	void VerticalScrollBar::OnChangeValue(System::Handler handler)
	{
		m_slider->OnChangeValue(handler);
	}

}