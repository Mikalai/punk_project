#ifndef _H_GUI_PUNK_BUTTON
#define _H_GUI_PUNK_BUTTON

#include "widget.h"

namespace GUI
{
	/*	maybe to use one func SetColor(FOR_WHAT_THE_COLOR, COLOR)	*/
	class LIB_GUI Button : public Widget
	{
		float m_backColorDown[4];
		float m_backColorUp[4];
		float m_backColorMouseOver[4];

		Button(const Button&);
		Button& operator = (const Button&);

	protected:
		virtual void OnIdle(System::IdleEvent* e);
		virtual void OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* e);
	public:

		Button(float x = 0, float y = 0, float width = 0.1, float height=0.01, const System::string& text = L"Button", Widget* parent = 0);
		virtual ~Button();
		void SetBackColorDown(float* c);
		void SetBackColorUp(float* c);
		void SetBackColorMouseOver(float* c);		
	};
}
#endif