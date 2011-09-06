#include "../system/allocator.h"
#include "../render/render.h"
#include "static_text.h"

namespace GUI
{
	StaticText::StaticText(int x, int y, int widthInSymbols, int heightInSymbols, int symbolSize) : 
	m_textRender(new Render::_2D::Text(x, y, widthInSymbols, heightInSymbols, symbolSize)), m_text("Text")
	{
		m_widthInSymbols = widthInSymbols;
		m_heightInSymbols = heightInSymbols;
		m_symbolSize = symbolSize;
		m_x = x;
		m_y = y;
		m_textRender->SetText(m_text.c_str());
	}

	StaticText::~StaticText()
	{
		delete m_textRender;
	}

	void StaticText::SetTextArea(int x, int y, int widthInSymbols, int heightInSymbols, int symbolSize)
	{
		if (m_textRender)
			delete m_textRender;
		m_textRender = new Render::_2D::Text(x, y, widthInSymbols, heightInSymbols, symbolSize);
		m_textRender->SetText(m_text.c_str());
	}

	void StaticText::SetText(const char* text)
	{
		m_text = text;
		m_textRender->SetText(m_text.c_str());
	}

	void StaticText::Render()
	{
		if (m_isVisible)
		{			
			m_textRender->SetSize(m_x, m_y, m_widthInSymbols*m_symbolSize, m_heightInSymbols*m_symbolSize);
			CommonStaff::g_renderPipeline.Add(m_textRender);
		}
	}
}