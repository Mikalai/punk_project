#ifndef _H_PUNK_CONSOLE
#define _H_PUNK_CONSOLE

#include <vector>
#include <string>
#include "widget.h"
#include "edit_box.h"
#include "../render/render.h"

namespace GUI
{
	class Console : public Widget
	{
		TextBox* m_textBox;
		Console();
		Console(const Console&);
		Console& operator = (const Console&);
		std::vector<System::string> m_messages;
	protected:
		virtual void RenderTextToTexture();
	public:		
		void Add(const System::string& text);
		virtual void Render();
		virtual bool EventHandler(System::Event* event);

		static Console* Get();
		static void Delete();
	};

}

#endif