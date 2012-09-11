#ifndef _H_PUNK_GUI_STATIC_TEXT_AREA
#define _H_PUNK_GUI_STATIC_TEXT_AREA

#include "widget.h"
#include "../render/2d/2d_text_area_render.h"

namespace GUI
{
	class StaticTextArea : public Widget
	{
		Render::TextAreaRender* m_textRender;
		StaticTextArea(const StaticTextArea&);		

	public:
		StaticTextArea(int x, int y, int width, int height, Widget* parent = 0);

		virtual void Render();

		virtual ~StaticTextArea();	
	};
}

#endif // _H_PUNK_GUI_STATIC_TEXT_AREA