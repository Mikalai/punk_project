#include "list_box.h"
#include <algorithm>
#include "gui_render.h"
#include "../utility/font_builder.h"

namespace GUI
{
	ListBox::ListBoxItem::ListBoxItem(const System::string& text, void* data)
		: m_text(text), m_data(data) 
	{	
	}

	void* ListBox::ListBoxItem::GetData()
	{
		return m_data;
	}

	const System::string& ListBox::ListBoxItem::GetText() const
	{
		return m_text;
	}

	void ListBox::ListBoxItem::SetText(const System::string& text) 
	{
		m_text = text;
	}

	void ListBox::ListBoxItem::SetData(void* data)
	{
		m_data = data;
	}

	ListBox::ListBox(float x, float y, float width, float height, Widget* parent) 
		: Widget(x, y, width, height, L"", parent), m_currentSelection(-1), m_startPosition(0)
	{
		m_scrollBar = new VerticalScrollBar(0.95f, 0, 0.05f, 1, this);
		m_scrollBar->OnChangeValue(System::EventHandler(this, &ListBox::OnScroll));
	}

	ListBox::~ListBox()
	{
		for (std::vector<ListBoxItem*>::iterator it = m_items.begin(); it != m_items.end(); it++)
		{
			delete (*it);
		}
	}

	void ListBox::OnScroll(System::Event*)
	{
		if (IsVisible() && IsEnabled())
		{
			m_startPosition = std::max(0, m_scrollBar->GetCurrent());
			RenderTextToTexture();
		}
	}

	void ListBox::SelectItem(int index)
	{
		if (index < 0)
		{
			m_currentSelection = -1;
			return;
		}
		if (index >= (int)m_items.size())
		{
			m_currentSelection = -1;
			return;
		}

		m_currentSelection = index;
		if (m_currentSelection > m_startPosition + GetMaxVisibleItems())
		{
			m_startPosition = m_currentSelection - GetMaxVisibleItems();
		}

		if (m_currentSelection < m_startPosition)
		{
			m_startPosition = m_currentSelection;
		}
		RenderTextToTexture();
	//	m_startPosition = std::max(0, m_currentSelection);

		//m_scrollBar->SetCurrent(m_currentSelection);
	}

	int ListBox::GetMaxVisibleItems() const
	{
		return int(GetScreenHeight() / (float)m_fontSize - 1.0f);
	}

	void ListBox::AddItem(ListBoxItem* item)
	{
		m_items.push_back(item);
		if ((int)m_items.size() > GetMaxVisibleItems())
			m_scrollBar->SetMax(m_items.size() - GetMaxVisibleItems());
		RenderTextToTexture();
	}

	void ListBox::RemoveItem(ListBoxItem* item)
	{
		std::vector<ListBoxItem*>::iterator it = std::find(m_items.begin(), m_items.end(), item);
		if (it != m_items.end())
		{
			delete *it;
			m_items.erase(it);
		}
		if ((int)m_items.size() > GetMaxVisibleItems())
			m_scrollBar->SetMax(m_items.size() - GetMaxVisibleItems());
		RenderTextToTexture();
	}

	int ListBox::GetItemsCount()
	{
		return m_items.size();
	}

	void ListBox::RemoveAllItems()
	{
		for each (ListBoxItem* item in m_items)
		{
			delete item;
		}
		m_items.clear();
		m_currentSelection = -1;
		m_startPosition = 0;
		m_scrollBar->SetCurrent(0);
		RenderTextToTexture();
	}

	void ListBox::RemoveItem(int position)
	{
		if (position < (int)m_items.size())
			m_items.erase(m_items.begin() + position);
		if ((int)m_items.size() > GetMaxVisibleItems())
			m_scrollBar->SetMax(m_items.size() - GetMaxVisibleItems());
		RenderTextToTexture();
	}

	void ListBox::InsertItem(ListBoxItem* item, int position)
	{
		if (position < (int)m_items.size())
			m_items.insert(m_items.begin() + position, item);
		if ((int)m_items.size() > GetMaxVisibleItems())
			m_scrollBar->SetMax(m_items.size() - GetMaxVisibleItems());
		RenderTextToTexture();
	}

	ListBox::ListBoxItem* ListBox::GetItem(int index)
	{
		if (index >= 0 && index < (int)m_items.size())
			return m_items[index];
		return 0;
	}

	void ListBox::Render(IGUIRender* render) const
	{
		render->RenderListBox(this);
		m_scrollBar->Render(render);
	}

	void ListBox::OnItemChanged(System::Handler h)
	{
		m_OnItemChanged = h;
	}

	void ListBox::OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			if (m_isCursorIn)
			{
				Math::vec2 p = Widget::WindowToViewport(float(e->x), float(e->y));
				float delta = GetHeight() - (p.Y() - GetY());
				float f = (m_text_texture->GetHeight() / (float)m_fontSize) / GetHeight() * delta;
				int new_selection = (float)m_startPosition +  f;
				if (new_selection >= m_items.size())
					new_selection = m_items.size()-1;

				if (new_selection != m_currentSelection)
				{
					m_OnItemChanged((System::Event*)new_selection);
				}
				m_currentSelection = new_selection;
				Widget::OnMouseLeftButtonDown(e);
			}
		}
	}

	void ListBox::OnMouseWheel(System::MouseWheelEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			int capacity = GetMaxVisibleItems();
			if (m_isCursorIn)
			{
				if (e->delta > 0)
				{
					if (m_startPosition > 0)
						m_startPosition--;
				}
				else 
				{
					if (m_startPosition + capacity < (int)m_items.size())
						m_startPosition++;						
				}
				m_scrollBar->SetCurrent(m_startPosition);
				RenderTextToTexture();
			}
			Widget::OnMouseWheel(e);
		}
	}

	void ListBox::OnKeyDown(System::KeyDownEvent* e)
	{
		switch(e->key)
		{
		case System::PUNK_KEY_UP:
			SelectItem(m_currentSelection == 0 ? 0 : m_currentSelection-1);
			break;
		case System::PUNK_KEY_DOWN:
			SelectItem(m_currentSelection == m_items.size() - 1 ? m_items.size()-1 : m_currentSelection+1);
			break;
		case System::PUNK_KEY_TAB:
			Widget::OnKeyDown(e);
			break;
		}
	}

	void ListBox::RenderTextToTexture()
	{
		int x = 2;
		int y = m_text_texture->GetHeight() - m_fontSize;
		m_text_texture->Fill(0);
		Utility::FontBuilder::Instance()->SetCurrentFace(m_font);
		Utility::FontBuilder::Instance()->SetCharSize(m_fontSize, m_fontSize);
		for (int i = m_startPosition; i < (int)m_items.size() && (i-m_startPosition)*m_fontSize < m_text_texture->GetHeight(); i++)
		{
			const System::string& s = m_items[i]->GetText();
			for (const wchar_t* a = s.Data();  *a; a++)
			{ 
				int width;
				int height;
				int x_offset;
				int y_offset;
				int x_advance;
				int y_advance;
				unsigned char* buffer;
				Utility::FontBuilder::Instance()->RenderChar(*a, &width, &height, &x_offset, &y_offset, &x_advance, &y_advance, &buffer);
				if (x + x_offset + width >= m_text_texture->GetWidth())
					break;
				m_text_texture->CopyFromCPU(x + x_offset, m_text_texture->GetHeight()- (y + y_offset), width, height, GL_RED, buffer);
				x += x_advance;				
			}
			y -= m_fontSize;
			x = 2;		
		}
	}
}