#ifndef _H_PUNK_GUI_SCROLL_BAR
#define _H_PUNK_GUI_SCROLL_BAR

#include <memory>
#include "widget.h"
#include "vertical_slider.h"
#include "button.h"

namespace GUI
{
	class IGUIRender;

	class LIB_GUI VerticalScrollBar : public Widget
	{		
		Button* m_upButton;
		VerticalSlider* m_slider;
		Button* m_downButton;
		float m_timer;

		void OnDownButtonLeftClick(System::Event* event);
		void OnUpButtonLeftClick(System::Event* event);

	protected:
		virtual void OnIdle(System::IdleEvent* event);
	public:

		VerticalScrollBar(float x = 0, float y = 0, float width = 0.1, float height = 1, Widget* parent = 0);
		virtual ~VerticalScrollBar();
		virtual void Render(IGUIRender* render) const;
		int GetCurrent() const;
		void SetCurrent(int value);
		void SetMax(int max);
		void OnChangeValue(System::Handler handler);
	};
}

#endif