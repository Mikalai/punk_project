#include "list_box.h"
#include <algorithm>

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

	ListBox::ListBox(int x, int y, int width, int height, Widget* parent) : Widget(x, y, width, height, parent), m_currentSelection(3), m_startPosition(0)
	{
		m_scrollBar = new VerticalScrollBar(width - 5, 0, 5, height, this);
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
		m_startPosition = m_scrollBar->GetCurrent();
		RenderTextToTexture();
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

	void ListBox::Render()
	{
		Widget::Render();		
		Render::TextAreaRender::Parameters* p = Render::TextAreaRender::Parameters::Create();
		p->Set((float)GetX(), (float)GetY(), (float)m_width, (float)m_height, m_textColor, &m_textTexture);
		Render::RenderPipeline::GetRenderPipeline()->Add(Render::TextAreaRender::GetRender(), p);

		if (m_currentSelection != -1 &&  (m_currentSelection - m_startPosition - 1) < m_height / m_fontSize && m_currentSelection - m_startPosition > 0)
		{
			float color[4] = {0.0f , 0.2f, 0.5f, 0.5f};
			Render::QuadRender::Parameters* p1 = Render::QuadRender::Parameters::Create();
			p1->Set(float(GetX()+1), float(GetY() + m_height - (m_currentSelection-m_startPosition)*m_fontSize-2), float(m_width - 2), float(m_fontSize+1), color);
			Render::RenderPipeline::GetRenderPipeline()->Add(Render::QuadRender::GetRender(), p1);
		}

		m_scrollBar->Render();
	}

	bool ListBox::EventHandler(System::Event* event)
	{
		switch(event->eventCode)
		{
		case System::EVENT_MOUSE_LBUTTON_DOWN:
			{
				System::MouseLeftButtonDownEvent* e = static_cast<System::MouseLeftButtonDownEvent*>(event);
				m_currentSelection = m_startPosition + m_height / m_fontSize - (e->y - GetY()) / m_fontSize;
			}
			break;			
		case System::EVENT_MOUSE_WHEEL:
			{
				System::MouseWheelEvent* e = static_cast<System::MouseWheelEvent*>(event);
				if (m_height / m_fontSize < m_items.size())
				{
					if (e->delta > 0)
					{
						if (m_startPosition > 0)
						{
							m_startPosition--;
							m_scrollBar->SetCurrent(m_scrollBar->GetCurrent() - 1);
						}
					}
					else 
					{
						if (m_items.size() - m_height / m_fontSize > m_startPosition)
						{
							m_startPosition++;
							m_scrollBar->SetCurrent(m_scrollBar->GetCurrent() + 1);
						}
					}
					RenderTextToTexture();
				}				
			}
			break;
		default:
			Widget::EventHandler(event);
		}
		return false;
	}

	void ListBox::RenderTextToTexture()
	{
		int x = 2;
		int y = m_height - m_fontSize;
		m_textTexture.Fill(0);
		Render::FontBuilder::SetCurrentFace(m_font);
		Render::FontBuilder::SetCharSize(m_fontSize, m_fontSize);
		for (int i = m_startPosition; i < (int)m_items.size()+m_startPosition && (i-m_startPosition)*m_fontSize < m_height; i++)
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
				Render::FontBuilder::RenderChar(*a, &width, &height, &x_offset, &y_offset, &x_advance, &y_advance, &buffer);
				if (x + x_offset + width >= m_textTexture.GetWidth())
					break;
				m_textTexture.CopyFromCPU(x + x_offset, m_textTexture.GetHeight() - (y + y_offset), width, height, ImageLoader::IMAGE_FORMAT_RED, buffer);
				x += x_advance;				
			}
			y -= m_fontSize;
			x = 2;		
		}
	}
}