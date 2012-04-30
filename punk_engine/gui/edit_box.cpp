#include "edit_box.h"
#include "../render/2d/2d_text_area_render.h"
#include "../render/font_builder.h"

namespace GUI
{
	TextBox::TextBox(int x, int y, int width, int height, Widget* parent) : Widget(x, y, width, height, parent)
	{
		m_textRender = Render::TextAreaRender::GetRender();
		RenderTextToTexture();
	}

	void TextBox::SetCursorPosition(int pos)
	{
		m_cursor_x = pos;
	}

	void TextBox::Render()
	{
		if (m_isVisible)
		{			
			Render::QuadRender::Parameters* p1 = Render::QuadRender::Parameters::Create();
			p1->m_back_color[0] = m_back_color[0]; p1->m_back_color[1] = m_back_color[1]; p1->m_back_color[2] = m_back_color[2]; p1->m_back_color[3] = m_back_color[3];
			p1->m_x = (float)GetX();
			p1->m_y = (float)GetY();
			p1->m_width = (float)m_width;
			p1->m_height = (float)m_height;
			//m_quadRender->SetSize(m_x, m_y, m_width, m_height);
			//m_quadRender.SetColor(m_back_color[0], m_back_color[1], m_back_color[2], m_back_color[3]);
			Render::RenderPipeline::GetRenderPipeline()->Add(m_quadRender, (void*)p1);

			Render::TextAreaRender::Parameters* p2 = Render::TextAreaRender::Parameters::Create();
			p2->m_back_color[0] = m_text_color[0]; p2->m_back_color[1] = m_text_color[1]; p2->m_back_color[2] = m_text_color[2]; p2->m_back_color[3] = m_text_color[3];
			p2->m_height = (float)m_height;
			p2->m_width = (float)m_width;
			p2->m_x = (float)(GetX()+5);
			p2->m_y = (float)(GetY()-2);	
			p2->m_texture = &m_textTexture;
			Render::RenderPipeline::GetRenderPipeline()->Add(m_textRender, (void*)p2);
		}
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

			Render::FontBuilder::RenderChar(m_text[i], &width, &height, &x_offset, &y_offset, &x_adv, &y_adv, &b);

			x += x_adv;
		}

		if (m_showCursor)
		{
			unsigned char data[128];
			memset(data, 0xFF, sizeof(data));
			m_textTexture.CopyFromCPU(x, 0, 2, m_textTexture.GetHeight(), ImageLoader::IMAGE_FORMAT_RED, data);			
		}
		else
		{
			unsigned char data[128];
			memset(data, 0, sizeof(data));
			m_textTexture.CopyFromCPU(x, 0, 2, m_textTexture.GetHeight(), ImageLoader::IMAGE_FORMAT_RED, data);
		}
	}

	bool TextBox::EventHandler(System::Event* event)
	{		
		switch(event->eventCode)
		{
		case System::EVENT_IDLE:
			{
				if (m_isFocused)
				{
					if (m_timer.GetElapsedTime() > 0.5)
					{
						InversCursor();
						m_timer.UpdateStartPoint();
					}

					m_back_color[0] += (m_back_color_0[0] - m_back_color[0]) / 2.0f;
					m_back_color[1] += (m_back_color_0[1] - m_back_color[1]) / 2.0f;
					m_back_color[2] += (m_back_color_0[2] - m_back_color[2]) / 2.0f;
					m_back_color[3] += (m_back_color_0[3] - m_back_color[3]) / 2.0f;	

					m_text_color[0] += (m_text_color_0[0] - m_text_color[0]) / 2.0f;
					m_text_color[1] += (m_text_color_0[1] - m_text_color[1]) / 2.0f;
					m_text_color[2] += (m_text_color_0[2] - m_text_color[2]) / 2.0f;
					m_text_color[3] += (m_text_color_0[3] - m_text_color[3]) / 2.0f;
				}
				else
				{
					if (m_showCursor == true)
					{
						InversCursor();
					}

					m_back_color[0] += (m_back_color_1[0] - m_back_color[0]) / 10.0f;
					m_back_color[1] += (m_back_color_1[1] - m_back_color[1]) / 10.0f;
					m_back_color[2] += (m_back_color_1[2] - m_back_color[2]) / 10.0f;
					m_back_color[3] += (m_back_color_1[3] - m_back_color[3]) / 10.0f;	

					m_text_color[0] += (m_text_color_1[0] - m_text_color[0]) / 10.0f;
					m_text_color[1] += (m_text_color_1[1] - m_text_color[1]) / 10.0f;
					m_text_color[2] += (m_text_color_1[2] - m_text_color[2]) / 10.0f;
					m_text_color[3] += (m_text_color_1[3] - m_text_color[3]) / 10.0f;
				}
			}
			break;		
		case System::EVENT_KEY_DOWN:
			{
				System::KeyDownEvent* e = static_cast<System::KeyDownEvent*>(event);
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
			break;
		case System::EVENT_KEY_CHAR:
			{
				//Driver::CheckError(L"KEY_CHAR");
					System::KeyCharEvent* e = static_cast<System::KeyCharEvent*>(event);
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
				break;
			}
		case System::EVENT_MOUSE_LBUTTON_DOWN:
			{
				System::MouseLeftButtonDownEvent* e = static_cast<System::MouseLeftButtonDownEvent*>(event);
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

						Render::FontBuilder::RenderChar(m_text[i], &width, &height, &x_offset, &y_offset, &x_adv, &y_adv, &b);
						x -= x_adv;
						if (x < 0)
							m_cursor_x = i;
					}
				}
			}
		default:
			Widget::EventHandler(event);
		}
		return false;
	}
}
