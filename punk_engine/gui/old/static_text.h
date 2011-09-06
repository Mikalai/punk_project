#ifndef _H_PUNK_STATIC_TEXT
#define _H_PUNK_STATIC_TEXT

#include <string>
#include "widget.h"
#include "../render/2d/2d_text.h"

namespace GUI
{
	class StaticText : public Widget
	{
		Render::_2D::Text* m_textRender;
		std::string m_text;
		
		int m_widthInSymbols;
		int m_heightInSymbols;
		int m_symbolSize;

		StaticText(const StaticText&);
	public:
		StaticText(int x, int y, int widthInSymbols, int heightInSymbols, int symbolSize = 14);

		void SetTextArea(int x, int y, int widthInSymbols, int heightInSymbols, int symbolHeight);
		void SetText(const char* text);

		virtual void Render();

		virtual ~StaticText();
	};

}

#endif