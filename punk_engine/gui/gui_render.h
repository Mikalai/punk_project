#ifndef _H_PUNK_GUI_RENDER
#define _H_PUNK_GUI_RENDER

namespace GUI
{
	class Widget;
	class ListBox;
	class VerticalSlider;
	class VerticalScrollbar;
	class TextBox;
	class ListBox;
	class TabWidget;
	class Balloon;
	
	class IGUIRender
	{
	public:
		virtual void Begin(int x, int y, int width, int height) = 0;
		virtual void End() = 0;
		virtual void RenderWidget(const Widget* widget) = 0;	
		virtual void RenderVerticalSlider(const VerticalSlider* slide) = 0;
		virtual void RenderTextBox(const TextBox* slide) = 0;
		virtual void RenderListBox(const ListBox* lb) = 0;
		virtual void RenderTabWidget(const TabWidget* lb) = 0;
		virtual void RenderBalloon(const Balloon* lb) = 0;
	};
}

#endif 