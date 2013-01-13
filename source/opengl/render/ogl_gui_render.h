#ifndef _H_PUNK_OPENGL_GUI_RENDER
#define _H_PUNK_OPENGL_GUI_RENDER

#include "../../gui/gui_render.h"
#include "../render_context/render_contexts.h"
#include "../textures/texture_context.h"
#include "render_state.h"

namespace OpenGL
{
	class GUIRender : public GUI::IGUIRender
	{
	public:
		GUIRender();
		virtual void Begin(int x, int y, int width, int height);
		virtual void End();
		virtual void RenderWidget(const GUI::Widget* widget);	
		//virtual void RenderVerticalSlider(const GUI::VerticalSlider* slide);
		//virtual void RenderTextBox(const GUI::TextBox* slide);
		//virtual void RenderListBox(const GUI::ListBox* lb);
		//virtual void RenderTabWidget(const GUI::TabWidget* lb);
		//virtual void RenderBalloon(const GUI::Balloon* lb);
	private:
		Math::vec4 m_selection_color_delta;
		System::Proxy<RenderContextGUI> m_rc;
		System::Proxy<TextureContext> m_tc;
		System::StateManager<OpenGL::CoreState> m_states;
	};
}

#endif