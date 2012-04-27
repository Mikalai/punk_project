#ifndef _H_PUNK_EDIT_BOX
#define _H_PUNK_EDIT_BOX

#include "widget.h"
#include "../system/timer.h"
#include "../render/2d/2d_text_area_render.h"

namespace GUI
{
	class TextBox : public Widget
	{
	protected:
		System::Timer m_timer;
		int m_cursor_x;
		bool m_showCursor;
		//Render::TextAreaRender* m_textRender;
		
		TextBox(const TextBox&);
		TextBox& operator = (const TextBox&);
	protected:
		void InversCursor();
	public:
		TextBox(int x = 0, int y = 0, int width = 100, int height = 100, Widget* parent = 0);
		void SetCursorPosition(int position);
		virtual void Render();
		virtual ~TextBox();
		virtual bool EventHandler(System::Event* event);
	};
}

#endif