#include <algorithm>
#include "edit_box.h"
#include "gui_render.h"
#include "../utility/font_builder.h"

namespace GUI
{
	TextBox::TextBox(float x, float y, float width, float height, Widget* parent) 
		: Widget(x, y, width, height, L"", parent)
		, m_cursor_x(0)
		, m_showCursor(true)		
	{
		SetVerticalTextAlign(VERTICAL_ALIGN_TOP);
		SetHorizontalTextAlign(HORIZONTAL_ALIGHT_LEFT);
		RenderTextToTexture();
	}

	void TextBox::SetCursorPosition(int pos)
	{
		m_cursor_x = pos;
	}

	void TextBox::Render(IGUIRender* render) const
	{
		if (IsVisible())
			render->RenderTextBox(this);
	}

	TextBox::~TextBox()
	{
	}

	void TextBox::InversCursor()
	{
		m_showCursor = !m_showCursor;

		int x = 0;
		int y = m_text_texture->GetHeight() - m_fontSize;
		int width = 0;
		int height = 14;
		int x_offset = 0;
		int y_offset = 0;
		int x_adv = 0;
		int y_adv = 0;
		unsigned char* b;
		for (int i = 0; i < m_cursor_x; i++)
		{			

			Utility::FontBuilder::Instance()->RenderChar(m_text[i], &width, &height, &x_offset, &y_offset, &x_adv, &y_adv, &b);

			if (x_offset < 0 && x == 0)
				x += -x_offset;
			if (x + x_offset + width >= m_text_texture->GetWidth())
			{
				y -= m_fontSize;
				x = 0;
				if (y < 0)
					return;
			}		
			x += x_adv;				
		}

		Utility::FontBuilder::Instance()->RenderChar('M', &width, &height, &x_offset, &y_offset, &x_adv, &y_adv, &b);
		
		if (m_showCursor)
		{
			unsigned char data[128];
			memset(data, 0xFF, sizeof(data));
			m_text_texture->CopyFromCPU(x + x_offset, m_text_texture->GetHeight() - (y + y_offset), 2, height, GL_RED, data);
			//m_text_texture->CopyFromCPU(x, (float)y*height, 2, height, GL_RED, data);			
		}
		else
		{
			unsigned char data[128];
			memset(data, 0, sizeof(data));
			m_text_texture->CopyFromCPU(x + x_offset, m_text_texture->GetHeight() - (y + y_offset), 2, height, GL_RED, data);
		}
	}

	void TextBox::OnKeyChar(System::KeyCharEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			if (m_isFocused)
			{
				//Driver::CheckError(L"KEY_CHAR");
				if (e->key == System::PUNK_KEY_BACKSPACE)
				{
					if (m_cursor_x > 0)
						m_text.Erase(--m_cursor_x, 1);
				}
				else if (e->key == System::PUNK_KEY_ENTER)
				{
				}
				else if (e->key == System::PUNK_KEY_TAB)
				{
				}
				else
				{					
					m_text.Insert(e->key, m_cursor_x++);
				}
				RenderTextToTexture();
			}
		}
	}

	void TextBox::OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			if (m_isCursorIn)
			{
				if (m_showCursor)
					InversCursor();
				int x = (int)GetX();
				x = e->x - x;
				m_cursor_x = m_text.Length();
				for (int i = 0; i < m_cursor_x; i++)
				{						
					int width;
					int height;
					int x_offset;
					int y_offset;
					int x_adv;
					int y_adv;
					unsigned char* b;

					Utility::FontBuilder::Instance()->RenderChar(m_text[i], &width, &height, &x_offset, &y_offset, &x_adv, &y_adv, &b);
					x -= x_adv;
					if (x < 0)
						m_cursor_x = i;
				}
			}
		}
	}	

	void TextBox::SetText(const System::string& text)
	{
		Widget::SetText(text);
		m_cursor_x = std::min(text.Length(), m_cursor_x);
	}

	void TextBox::OnKeyDown(System::KeyDownEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			switch(e->key)
			{
			case System::PUNK_KEY_LEFT:
				{
					if (m_showCursor)
						InversCursor();

					if (!System::Keyboard::Instance()->GetKeyState(System::PUNK_KEY_CONTROL))
					{
						if (m_cursor_x > 0)
							m_cursor_x--;
					}
					else
					{
						int new_pos = m_cursor_x-1;
						while (new_pos >= 0 && m_text[new_pos] != L' ')
						{
							new_pos--;
						}
						m_cursor_x = std::max(0, new_pos);
					}
				}
				break;
			case System::PUNK_KEY_RIGHT:
				{
					if (m_showCursor)
						InversCursor();
					if (!System::Keyboard::Instance()->GetKeyState(System::PUNK_KEY_CONTROL))
					{
						if (m_cursor_x < (int)m_text.Length())
							m_cursor_x++;						
					}
					else
					{
						int new_pos = m_cursor_x+1;
						while (new_pos < m_text.Length() && m_text[new_pos] != L' ')
						{
							new_pos++;
						}						
						m_cursor_x = std::min(m_text.Length(), new_pos);
					}
					break;
				}
			case System::PUNK_KEY_HOME:
				{					
					if (m_showCursor)
						InversCursor();
					m_cursor_x = 0;
				}
				break;
			case System::PUNK_KEY_END:
				{
					if (m_showCursor)
						InversCursor();
					m_cursor_x = m_text.Length();
				}
				break;
			case System::PUNK_KEY_TAB:
				{
					if (m_showCursor)
						InversCursor();
					Widget::OnKeyDown(e);
				}
				break;
			case System::PUNK_KEY_UP:
				break;
			case System::PUNK_KEY_DOWN:
				break;
			case System::PUNK_KEY_DELETE:
				{
					if (m_cursor_x < (int)m_text.Length())
						m_text.Erase(m_cursor_x, 1);
					RenderTextToTexture();
				}
				break;
			default:
				break;
			}
		}
	}

	void TextBox::OnIdle(System::IdleEvent* e)
	{
		if (IsVisible() && IsEnabled())
		{
			if (m_isFocused)
			{
				if (m_timer.GetElapsedTime() > 0.5)
				{
					InversCursor();
					m_timer.UpdateStartPoint();
				}
			}
			else
			{
				if (m_showCursor)
				{
					InversCursor();
				}
			}
			Widget::OnIdle(e);
		}
	}
}
