#include "list_box.h"
#include <algorithm>
#include "gui_render.h"
#include "../utility/font_builder.h"

namespace GUI
{
	ListBox::ListBoxItem::ListBoxItem(const char* text, void* data) : m_text(text), m_data(data) 
	{	}
	
	void* ListBox::ListBoxItem::GetData()
	{
		return m_data;
	}

	const char* ListBox::ListBoxItem::GetText() const
	{
		return m_text.c_str();
	}

	void ListBox::ListBoxItem::SetText(const char* text) 
	{
		m_text = text;
	}

	void ListBox::ListBoxItem::SetData(void* data)
	{
		m_data = data;
	}

	ListBox::ListBox(float x, float y, float width, float height, Widget* parent) : Widget(x, y, width, height, parent), m_currentSelection(3), m_startPosition(0)
	{
		m_scrollBar = new VerticalScrollBar(0.95, 0, 0.05, 1, this);
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
		m_startPosition = max(0, m_scrollBar->GetCurrent());
		RenderTextToTexture();
		}
	}

	int ListBox::GetMaxVisibleItems() const
	{
		return m_height / m_fontSize+1;
	}

	void ListBox::AddItem(ListBoxItem* item)
	{
		m_items.push_back(item);
		if (m_items.size() > GetMaxVisibleItems())
			m_scrollBar->SetMax(m_items.size() - GetMaxVisibleItems());
		RenderTextToTexture();
	}

	void ListBox::RemoveItem(ListBoxItem* item)
	{
		std::vector<ListBoxItem*>::iterator it = std::find(m_items.begin(), m_items.end(), item);
		if (it != m_items.end())
			m_items.erase(it);
		if (m_items.size() > GetMaxVisibleItems())
			m_scrollBar->SetMax(m_items.size() - GetMaxVisibleItems());
		RenderTextToTexture();
	}

	void ListBox::RemoveItem(int position)
	{
		if (position < (int)m_items.size())
			m_items.erase(m_items.begin() + position);
		if (m_items.size() > GetMaxVisibleItems())
			m_scrollBar->SetMax(m_items.size() - GetMaxVisibleItems());
		RenderTextToTexture();
	}

	void ListBox::InsertItem(ListBoxItem* item, int position)
	{
		if (position < (int)m_items.size())
			m_items.insert(m_items.begin() + position, item);
		if (m_items.size() > GetMaxVisibleItems())
			m_scrollBar->SetMax(m_items.size() - GetMaxVisibleItems());
		RenderTextToTexture();
	}

	void ListBox::Render(IGUIRender* render) const
	{
		render->RenderListBox(this);
		m_scrollBar->Render(render);
	}

	void ListBox::OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
		if (m_isCursorIn)
		{
			Math::vec2 p = Widget::WindowToViewport(e->x, e->y);
			float delta = GetHeight() - (p.Y() - GetY());
			float f = (m_text_texture->GetHeight() / (float)m_fontSize) / GetHeight() * delta;
			m_currentSelection = m_startPosition +  f;
			if (m_currentSelection >= m_items.size())
				m_currentSelection = m_items.size() - 1;
			Widget::OnMouseLeftButtonDown(e);
		}
		}
	}

	void ListBox::OnMouseWheel(System::MouseWheelEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
		int capacity = m_text_texture->GetHeight() / m_fontSize;
		if (m_isCursorIn)
		{
				if (e->delta > 0)
				{
					if (m_startPosition > 0)
						m_startPosition--;
				}
				else 
				{
					if (m_startPosition + capacity < m_items.size())
						m_startPosition++;						
				}
				m_scrollBar->SetCurrent(m_startPosition);
				RenderTextToTexture();
		}
		Widget::OnMouseWheel(e);
		}
	}

	void ListBox::RenderTextToTexture()
	{
		int x = 2;
		int y = m_text_texture->GetHeight() - m_fontSize;
		m_text_texture->Fill(0);
		Utility::FontBuilder::GetInstance()->SetCurrentFace(m_font);
		Utility::FontBuilder::GetInstance()->SetCharSize(m_fontSize, m_fontSize);
		for (int i = m_startPosition; i < (int)m_items.size() && (i-m_startPosition)*m_fontSize < m_text_texture->GetHeight(); i++)
		{
			for (const char* a = m_items[i]->GetText();  *a; a++)
			{ 
				int width;
				int height;
				int x_offset;
				int y_offset;
				int x_advance;
				int y_advance;
				unsigned char* buffer;
				Utility::FontBuilder::GetInstance()->RenderChar(*a, &width, &height, &x_offset, &y_offset, &x_advance, &y_advance, &buffer);
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