#ifndef _H_PUNK_GUI_TAB_WIDGET
#define _H_PUNK_GUI_TAB_WIDGET

#include "widget.h"
#include <memory>

namespace GUI
{
	class IGUIRender;

	class LIB_GUI TabWidget : public Widget
	{
		Widget* m_buttons;
		int m_active_tab;
	public:		
		TabWidget(float x = 0, float y = 0, float w = 1, float h = 1, Widget* p = 0);
		void AddTab(const System::string& name, Widget* widget);
		void SetContent(int tab, Widget* widget);
		void SetActiveTab(int tab); 
		int GetActiveTab(int tab); 
		Widget* GetTab(int tab); 
		const Widget* GetTab(int tab) const;
		virtual void SetNextWidget(Widget* widget);		
		virtual void SetPrevWidget(Widget* widget);
		virtual void Render(IGUIRender* render) const;
		Widget* GetFirstTabButton();
		Widget* GetLastTabButton();
	protected:
		void SwitchTab(System::Event*);
	};
}

#endif