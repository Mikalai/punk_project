#include "int_watcher.h"
#include "button.h"
#include "static_text_area.h"

namespace GUI
{
	IntWatcher::IntWatcher(int x, int y, int width, int height, Widget* parent) :
Widget(x, y, width, height, parent)
{	
	m_isMinimized = false;
	m_button = new Button(0, this->GetHeight() - 20, width, 20, L" System", this);
	m_button->OnLeftClick(System::EventHandler(this, &IntWatcher::OnButtonClick));	
	FixPosition(false);
}

void IntWatcher::Add(const int* variable, const char* desc)
{
	Item* item = new Item();
	item->m_desc = desc;
	item->m_text = new StaticTextArea(5, this->GetHeight() - 40 - 20*m_items.size(), m_width, 20, this);
	//item->m_text->SetColor(ColorType::ACTIVE_COLOR, 1,1,1,1);
	//item->m_text->SetColor(ColorType::INACTIVE_COLOR, 0.8, 0.8, 0.8,1);
	item->m_variable = variable;

	m_items.push_back(item);
}

void IntWatcher::OnButtonClick(System::Event* event)
{		
	m_isMinimized = !m_isMinimized;
	if (m_isMinimized)
	{
		m_prev_height = m_height;
		m_y += m_height - 20;
		m_height = 20;		
		m_button->SetY(m_height - 20);		
	}
	else
	{
		m_height = m_prev_height;
		m_y -= m_prev_height - 20;
		m_button->SetY(m_height - 20);		
	}

	for (std::vector<Item*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
	{
		if (m_isMinimized)
		{
			//(*it)->m_text->SetY(m_height - 40);
		}
		else
		{
			//(*it)->m_text->SetY(m_height - 40);
		}
		(*it)->m_text->Show(!m_isMinimized);
	}
}

IntWatcher::~IntWatcher()
{
	for( std::vector<Item*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
	{
		delete (*it);
	}
	m_items.clear();
}

void IntWatcher::Render()
{
	if (!m_isMinimized)
	{
		if (m_timer.GetElapsedTime() > 1.0)
		{
		for (std::vector<Item*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		{
			if ((*it)->m_variable && (*it)->m_prev_value != *(*it)->m_variable)
			{
				char tmp[128];
				char buf[256];			
				itoa(*(*it)->m_variable, tmp, 10);	
				sprintf(buf, "%s%s", (*it)->m_desc, tmp);
				//(*it)->m_text->SetTextSize(10);
				(*it)->m_text->SetText(buf);
			}
		}
		m_timer.UpdateStartPoint();
		}
	}	
	Widget::Render();		
}
}