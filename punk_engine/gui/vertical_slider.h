#ifndef _H_PUNK_VERTICAL_SLIDER
#define _H_PUNK_VERTICAL_SLIDER

#include "widget.h"

namespace GUI
{
	class IGUIRender;

	class LIB_GUI VerticalSlider : public Widget
	{
		int m_min;
		int m_max;
		int m_cur;
		int m_prev;
	protected:
		System::Handler m_onChangeValue;

		virtual void OnIdle(System::IdleEvent* e);
		virtual void OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* e);
		virtual void OnMouseMove(System::MouseMoveEvent* e);

	public:
		VerticalSlider(float x = 0, float y = 0, float width = 1, float height = 0.1, int min_value = 0, int max_value = 100, Widget* parent = 0);
		virtual ~VerticalSlider();
		void SetMin(int min);
		void SetMax(int max);
		void SetCurrent(int value);
		int GetMin() const;
		int GetMax() const;
		int GetCurrent() const;
		void SetBounds(int min, int max);
		void OnChangeValue(System::Handler onChangeValue);

		virtual void Render(IGUIRender* render) const;
	};
}

#endif