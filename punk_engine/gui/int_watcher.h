#ifndef _H_PUNK_INT_WATCHER
#define _H_PUNK_INT_WATCHER

#include "widget.h"
#include "../system/timer.h"
#include <vector>

namespace GUI
{
	class Button;
	class StaticTextArea;

	class IntWatcher : public Widget
	{
		struct Item
		{
			const int* m_variable;	
			int m_prev_value;
			const char* m_desc;
			StaticTextArea* m_text;
		};

		std::vector<Item*> m_items;
		Button* m_button;		
		bool m_isMinimized;
		int m_prev_width;
		int m_prev_height;
		System::Timer m_timer;
	protected:
		void OnButtonClick(System::Event* event);
	public:

		IntWatcher(int x = 0, int y = 0, int width = 100, int height = 200, Widget* parent = 0);
		void Add(const int* element, const char* description);

		virtual void Render();
		virtual ~IntWatcher();
	};
}

#endif