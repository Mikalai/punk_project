#ifndef _H_PUNK_OPENGL_GUI_RENDER
#define _H_PUNK_OPENGL_GUI_RENDER

#include "../../gui/gui_render.h"
#include "../../gpu/module.h"

namespace Render
{
	class GUIRender : public GUI::IGUIRender
	{
	public:
		GUIRender(Gpu::VideoDriver* driver);
		virtual ~GUIRender();
		virtual void Begin(int x, int y, int width, int height);
		virtual void End();
		virtual void RenderWidget(const GUI::Widget* widget);	
		//virtual void RenderVerticalSlider(const GUI::VerticalSlider* slide);
		//virtual void RenderTextBox(const GUI::TextBox* slide);
		//virtual void RenderListBox(const GUI::ListBox* lb);
		//virtual void RenderTabWidget(const GUI::TabWidget* lb);
		//virtual void RenderBalloon(const GUI::Balloon* lb);
	private:
		void Clear();

	private:
		Math::vec4 m_selection_color_delta;
		//System::StateManager<Gpu::CoreState> m_states;

		//	next pointers should be destroyed in destructor		
        Gpu::TextureContext* m_tc;

		//	next pointers should not be destroyed in destructor
		Gpu::AbstractRenderPolicy* m_rc;		

		Gpu::QuadObject m_quad;
	};
}

#endif
