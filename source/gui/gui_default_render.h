#ifndef _H_PUNK_GUI_DEFAULT_RENDER
#define _H_PUNK_GUI_DEFAULT_RENDER

#include <memory>
#include "gui_render.h"
#include "../system/driver/video/driver.h"

namespace GUI
{
	class DefaultGUIRender : public IGUIRender
	{
		Math::vec4 m_selection_color_delta;
		std::auto_ptr<OpenGL::QuadObject> m_quad;
		std::auto_ptr<OpenGL::RenderContextGUI> m_rc;
		std::auto_ptr<OpenGL::TextureContext> m_tc;
	public:
		DefaultGUIRender();
		virtual ~DefaultGUIRender();
		virtual void Begin(int x, int y, int width, int height);
		virtual void End();
		virtual void RenderWidget(const Widget* widget);	
		virtual void RenderVerticalSlider(const VerticalSlider* slide);
		virtual void RenderTextBox(const TextBox* slide);
		virtual void RenderListBox(const ListBox* lb);
		virtual void RenderTabWidget(const TabWidget* lb);
		virtual void RenderBalloon(const Balloon* lb);
	};
}

#endif