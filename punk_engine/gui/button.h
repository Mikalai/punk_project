#ifndef _H_GUI_PUNK_BUTTON
#define _H_GUI_PUNK_BUTTON

#include "widget.h"
#include "../render/2d/2d_quad_render.h"
#include "../render/2d/2d_text_area_render.h"

namespace GUI
{
	/*	maybe to use one func SetColor(FOR_WHAT_THE_COLOR, COLOR)	*/
	class Button : public Widget
	{
		float m_backColorDown[4];
		float m_backColorUp[4];
		float m_backColorMouseOver[4];
		
		Render::QuadRender* m_quadRender;
		Render::TextAreaRender* m_textRender; 

		Button(const Button&);
		Button& operator = (const Button&);

	public:

		Button(int x, int y, int width, int height, const System::string& text, Widget* parent = 0);
		virtual ~Button();

		virtual void Render();
		virtual bool EventHandler(System::Event* event);
		void SetBackColorDown(float* c);
		void SetBackColorUp(float* c);
		void SetBackColorMouseOver(float* c);
	};
}
#endif