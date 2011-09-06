#ifndef _H_PUNK_LIST_BOX
#define _H_PUNK_LIST_BOX

#include "widget.h"
#include "../render/render.h"
#include "vertical_scrollbar.h"

namespace GUI
{
	class ListBox : public Widget
	{
	public:
		class ListBoxItem
		{
			std::string m_text;
			void* m_data;
		public:
			ListBoxItem(const char* text, void* data = 0);
			void SetText(const char* text);
			const char* GetText() const;
			void SetData(void* data);
			void* GetData();
		};

	private:
		int m_currentSelection;
		int m_startPosition;
		std::vector<ListBoxItem*> m_items;
		
		GUI::VerticalScrollBar* m_scrollBar;

		ListBox(const ListBox&);
		ListBox& operator = (ListBox&);
	protected:
		virtual void RenderTextToTexture();
		int GetMaxVisibleItems() const;
		void OnScroll(System::Event*);
	public:
		ListBox(int x = 0, int y = 0, int width = 0, int height = 0, Widget* parent = 0);
		void AddItem(ListBoxItem* item);
		void RemoveItem(int position);
		void RemoveItem(ListBoxItem* item);
		void InsertItem(ListBoxItem* item, int position);
		virtual ~ListBox();
		virtual void Render();
		virtual bool EventHandler(System::Event* event);
	};
}

#endif