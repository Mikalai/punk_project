#ifndef _H_PUNK_LIST_BOX
#define _H_PUNK_LIST_BOX

#include "widget.h"
#include "vertical_scrollbar.h"

namespace GUI
{
	class IGUIRender;

	class LIB_GUI ListBox : public Widget
	{
	public:

		class LIB_GUI ListBoxItem
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

		virtual void OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* e);
		virtual void OnMouseWheel(System::MouseWheelEvent* e);

	public:
		ListBox(float x = 0, float y = 0, float width = 0.1, float height = 1, Widget* parent = 0);
		void AddItem(ListBoxItem* item);
		void RemoveItem(int position);
		void RemoveItem(ListBoxItem* item);
		void InsertItem(ListBoxItem* item, int position);
		int GetCurrentSelection() const { return m_currentSelection; }
		int GetStartOffset() const { return m_startPosition; }
		virtual ~ListBox();
		virtual void Render(IGUIRender* render) const;
	};
}

#endif