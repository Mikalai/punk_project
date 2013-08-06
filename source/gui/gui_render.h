#ifndef _H_PUNK_GUI_RENDER_2
#define _H_PUNK_GUI_RENDER_2

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
		//virtual void RenderVerticalSlider(const VerticalSlider* slide) override;
		//virtual void RenderTextBox(const TextBox* slide) override;
		//virtual void RenderListBox(const ListBox* lb) override;
		//virtual void RenderTabWidget(const TabWidget* lb) override;
		//virtual void RenderBalloon(const Balloon* lb) override;
	};
}

#endif //	_H_PUNK_GUI_RENDER_2
