#include "edit_box.h"
#include "gui_render.h"
#include "../utility/font_builder.h"

namespace GUI
{
	TextBox::TextBox(float x, float y, float width, float height, Widget* parent) : Widget(x, y, width, height, parent)
	{
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
		for (int i = 0; i < m_cursor_x; i++)
		{
			int width;
			int height;
			int x_offset;
			int y_offset;
			int x_adv;
			int y_adv;
			unsigned char* b;

			Utility::FontBuilder::GetInstance()->RenderChar(m_text[i], &width, &height, &x_offset, &y_offset, &x_adv, &y_adv, &b);

			x += x_adv;
		}

		if (m_showCursor)
		{
			unsigned char data[128];
			memset(data, 0xFF, sizeof(data));
			m_text_texture->CopyFromCPU(x, 0, 2, m_text_texture->GetHeight(), GL_RED, data);			
		}
		else
		{
			unsigned char data[128];
			memset(data, 0, sizeof(data));
			m_text_texture->CopyFromCPU(x, 0, 2, m_text_texture->GetHeight(), GL_RED, data);
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
			int x = GetX();
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

				Utility::FontBuilder::GetInstance()->RenderChar(m_text[i], &width, &height, &x_offset, &y_offset, &x_adv, &y_adv, &b);
				x -= x_adv;
				if (x < 0)
					m_cursor_x = i;
			}
		}
		}
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
				if (m_cursor_x > 0)
					m_cursor_x--;
			}
			break;
		case System::PUNK_KEY_RIGHT:
			{
				if (m_showCursor)
					InversCursor();
				if (m_cursor_x < (int)m_text.Length())
					m_cursor_x++;						
				break;
			}
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
