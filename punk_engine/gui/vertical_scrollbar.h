#ifndef _H_PUNK_GUI_SCROLL_BAR
#define _H_PUNK_GUI_SCROLL_BAR

#include "widget.h"
#include "vertical_slider.h"
#include "button.h"

namespace GUI
{
	class VerticalScrollBar : public Widget
	{		
		Button* m_upButton;
		VerticalSlider* m_slider;
		Button* m_downButton;

		void OnDownButtonLeftClick(System::Event* event);
		void OnUpButtonLeftClick(System::Event* event);
	
	public:
		VerticalScrollBar(int x = 0, int y = 0, int width = 20, int height = 100, Widget* parent = 0);
		virtual ~VerticalScrollBar();
		virtual void Render();
		int GetCurrent() const;
		void SetCurrent(int value);
		void SetMax(int max);
		void OnChangeValue(System::Handler handler);
	};
}

#endif