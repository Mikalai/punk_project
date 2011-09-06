#ifndef _H_PUNK_VERTICAL_SLIDER
#define _H_PUNK_VERTICAL_SLIDER

#include "widget.h"
#include "../render/render.h"

namespace GUI
{
	class VerticalSlider : public Widget
	{
		int m_min;
		int m_max;
		int m_cur;
		int m_prev;
	protected:
		System::Handler m_onChangeValue;

	public:
		VerticalSlider(int x = 0, int y = 0, int width = 20, int height = 200, int min_value = 0, int max_value = 100, Widget* parent = 0);
		virtual ~VerticalSlider();
		void SetMin(int min);
		void SetMax(int max);
		void SetCurrent(int value);
		int GetMin() const;
		int GetMax() const;
		int GetCurrent() const;
		void SetBounds(int min, int max);

		void OnChangeValue(System::Handler onChangeValue);

		virtual bool EventHandler(System::Event* event);
		virtual void Render();
	};
}

#endif