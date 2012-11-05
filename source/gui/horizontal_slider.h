#ifndef _H_PUNK_HORIZONTAL_SLIDER
#define _H_PUNK_HORIZONTAL_SLIDER

#include "widget.h"
#include "../render/render.h"

namespace GUI
{
	class HorizontalSlider : public Widget
	{
		Render::QuadRender* m_quadRender;
		Render::TextAreaRender* m_textRender;
		int m_min;
		int m_max;
		int m_cur;
		int m_prev;
	protected:
		System::Handler m_onChangeValue;

	public:
		HorizontalSlider(int x = 0, int y = 0, int width = 200, int height = 20, int min_value = 0, int max_value = 100, Widget* parent = 0);
		virtual ~HorizontalSlider();
		void SetMin(int Min);
		void SetMax(int Max);
		void SetCurrent(int value);
		int GetMin() const;
		int GetMax() const;
		int GetCurrent() const;
		void SetBounds(int Min, int Max);

		void OnChangeValue(System::Handler onChangeValue);

		virtual bool EventHandler(System::Event* event);
		virtual void Render();
	};
}

#endif