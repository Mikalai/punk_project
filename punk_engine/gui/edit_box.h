#ifndef _H_PUNK_EDIT_BOX
#define _H_PUNK_EDIT_BOX

#include "widget.h"
#include "../system/timer.h"

namespace GUI
{
	class IGUIRender;

	class LIB_GUI TextBox : public Widget
	{
	protected:
		System::Timer m_timer;
		int m_cursor_x;
		bool m_showCursor;
		
		TextBox(const TextBox&);
		TextBox& operator = (const TextBox&);
	protected:
		void InversCursor();
		virtual void OnKeyChar(System::KeyCharEvent* e);
		virtual void OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* e);
		virtual void OnKeyDown(System::KeyDownEvent* e);
		virtual void OnIdle(System::IdleEvent* e);
	public:
		TextBox(float x = 0, float y = 0, float width = 0.1, float height = 0.05, Widget* parent = 0);
		void SetCursorPosition(int position);
		virtual void Render(IGUIRender* render) const; 
		virtual ~TextBox();
	};
}

#endif