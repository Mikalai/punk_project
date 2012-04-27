#ifndef _H_PUNK_GUI_RENDER
#define _H_PUNK_GUI_RENDER

namespace GUI
{
	class Widget;

	class IGUIRender
	{
	public:
		virtual void Begin(int x, int y, int width, int height) = 0;
		virtual void End() = 0;
		virtual void RenderWidget(const Widget* widget) = 0;
	};
}

#endif 