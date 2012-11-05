#ifndef _H_PUNK_VERTICAL_SLIDER
#define _H_PUNK_VERTICAL_SLIDER

#include "widget.h"

namespace GUI
{
	class Button;
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
		virtual void OnMouseWheel(System::MouseWheelEvent* e);

	public:
		VerticalSlider(float x = 0, float y = 0, float width = 1, float height = 0.1, int min_value = 0, int max_value = 100, Widget* parent = 0);
		virtual ~VerticalSlider();
		void SetMin(int Min);
		void SetMax(int Max);
		void SetCurrent(int value);
		int GetMin() const;
		int GetMax() const;
		int GetCurrent() const;
		void SetBounds(int Min, int Max);
		void OnChangeValue(System::Handler onChangeValue);

		const VerticalSlider* GetSlider() const;
		const Button* GetTopButton() const;
		const Button* GetBottonButton() const;
		virtual void Render(IGUIRender* render) const;
	};
}

#endif