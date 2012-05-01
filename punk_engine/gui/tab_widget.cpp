#include "tab_widget.h"
#include "button.h"
#include "gui_render.h"

namespace GUI
{
	TabWidget::TabWidget(float x, float y, float w, float h, Widget* p)
		: Widget(x, y, w, h, p)
		, m_active_tab(-1)
	{
		SetText(L"");
		Widget* widget = new Widget(0, 0, 1, 0.05, this);
		widget->SetText(L"");
		m_buttons = widget;			
	}

	void TabWidget::SetContent(int tab, Widget* widget)
	{	
		m_children[tab].reset(widget);
	}

	void TabWidget::AddTab(const System::string& name, Widget* widget)
	{
		if (m_active_tab == -1)
		{
			m_active_tab = GetChildrenCount();
			widget->Show(true);
		}
		else
			widget->Show(false);
		widget->SetSize(0, 0.05, 1, 0.95);
		int index = GetChildrenCount();
		widget->SetAnyData((void*)index);
		AddChild(widget);
		//
		//	create a button for this tab
		//				
		float x_pos = m_buttons->GetChildrenCount() * 0.1;
		Button* btn = new Button(x_pos, 0, 0.1, 1, name, m_buttons);
		btn->SetMouseLeftClickHandler(System::EventHandler(btn, this, &TabWidget::SwitchTab));
		btn->SetAnyData((void*)widget);
	}

	void TabWidget::SwitchTab(System::Event* e)
	{
		if (e->reciever != 0)
		{
			Button* btn = static_cast<Button*>(e->reciever);
			Widget* widget = static_cast<Widget*>(btn->GetAnyData());
			m_children[m_active_tab]->Show(false);
			m_active_tab = (int)widget->GetAnyData();
			m_children[m_active_tab]->Show(true);
		}
	}
	
	void TabWidget::SetActiveTab(int tab)
	{
		if (m_active_tab != -1)
			m_children[m_active_tab]->Show(false);

		m_active_tab = tab; 
		m_children[m_active_tab]->Show(true);
	}

	int TabWidget::GetActiveTab(int tab)
	{
		return m_active_tab; 
	}

	Widget* TabWidget::GetTab(int tab)
	{
		return m_children[tab].get();
	}

	const Widget* TabWidget::GetTab(int tab) const
	{
		return m_children[tab].get();
	}
	
	void TabWidget::Render(IGUIRender* render) const
	{
		render->RenderWidget(this);
	}
}