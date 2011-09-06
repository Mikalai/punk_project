#include "console.h"

namespace GUI
{
	Console* g_console;

	Console* Console::Get()
	{
		if (g_console)
			return g_console;
		g_console = new Console();
		return g_console;
	}

	void Console::Delete()
	{
		if (g_console)
		{
			delete g_console;
			g_console = 0;
		}
	}

	Console::Console() : Widget(0, System::g_desktop->GetHeight() / 2, System::g_desktop->GetWidth(), System::g_desktop->GetHeight() / 2)
	{
		m_width = System::g_desktop->GetWidth();
		m_height = System::g_desktop->GetHeight() / 2;
		m_x = 0;
		m_y = m_height;
		m_fontSize = 12;

		m_textBox = new TextBox( 0, 0, m_width, 20, this);
	}

	void Console::Render()
	{
		if (m_isVisible)
		{		
			Render::QuadRender::Parameters* p = Render::QuadRender::Parameters::Create();
			p->Set((float)GetX(), (float)GetY(), (float)m_width, (float)m_height, m_color);
			Render::RenderPipeline::GetRenderPipeline()->Add(Render::QuadRender::GetRender(), p);
			Render::TextAreaRender::Parameters* p2 = Render::TextAreaRender::Parameters::Create();
			p2->Set((float)GetX(), (float)GetY(), (float)m_width, (float)m_height, m_textColor, &m_textTexture);
			Render::RenderPipeline::GetRenderPipeline()->Add(Render::TextAreaRender::GetRender(), p2);
			m_textBox->Render();
			Render::LineRender::Parameters* p3 = Render::LineRender::Parameters::Create();
			p3->Set(float(GetX()+10), float(GetY() + 20), float(GetX() + m_width-10), float(GetY() + 20), m_inactiveColor);
			Render::RenderPipeline::GetRenderPipeline()->Add(Render::LineRender::GetRender(), p3);
		}
	}

	void Console::Add(const System::string& text)
	{
		System::string s = text;
		s.Insert(L'>', 0);
		m_messages.push_back(s);
		RenderTextToTexture();
	}

	void Console::RenderTextToTexture()
	{
		int x = 10;
		int y = m_fontSize+20;
		m_textTexture.Fill(0);
		Render::FontBuilder::SetCurrentFace(m_font);
		Render::FontBuilder::SetCharSize(m_fontSize, m_fontSize);
		for (std::vector<System::string>::const_reverse_iterator it = m_messages.crbegin(); it != m_messages.crend(); ++it)
		{
			for (int start = it->Length() / (m_width/m_fontSize); start >= 0; start--)
			{
				for (int i = start*m_width/m_fontSize;  i < it->Length() && i < (start+1)*m_width/m_fontSize; i++)
				{ 
					int width;
					int height;
					int x_offset;
					int y_offset;
					int x_advance;
					int y_advance;
					unsigned char* buffer;
					Render::FontBuilder::RenderChar((*it)[i], &width, &height, &x_offset, &y_offset, &x_advance, &y_advance, &buffer);
					if (x + x_offset + width >= m_textTexture.GetWidth())
					{
						y += m_fontSize;
						x = 10;
						if (y < 0)
							return;
					}				
					m_textTexture.CopyFromCPU(x + x_offset, m_textTexture.GetHeight() - (y + y_offset), width, height, ImageLoader::IMAGE_FORMAT_RED, buffer);
					x += x_advance;				
				}
				y += m_fontSize;
				x = 10;
			}
		}
	}

	bool Console::EventHandler(System::Event* event)
	{
		Widget::EventHandler(event);

		switch(event->eventCode)
		{
		case System::EVENT_WINDOW_RESIZE:
			{
				m_width = System::g_desktop->GetWidth();
				m_height = System::g_desktop->GetHeight()/2;
				m_x = 0;
				m_y = System::g_desktop->GetHeight()/2;
				m_textTexture.Resize(m_width, m_height);
				RenderTextToTexture();
				m_textBox->SetSize(0, 0, m_width, 20);
			}
			break;
		case System::EVENT_KEY_CHAR:
			{
				System::KeyCharEvent* e = static_cast<System::KeyCharEvent*>(event);
				if (e->key == '`' || e->key == '~')
					Show(!m_isVisible);
				else if (e->key == System::PUNK_KEY_ENTER)
				{					
					Add(m_textBox->GetText());
					m_textBox->SetText("");
					m_textBox->SetCursorPosition(0);
				}
			}
			break;
		}

		return true;
	}
}