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
			System::string m_text;
			void* m_data;
		public:
			ListBoxItem(const System::string& text, void* data = 0);
			void SetText(const System::string& text);
			const System::string& GetText() const;
			void SetData(void* data);
			void* GetData();
		};

	private:
		System::Handler m_OnItemChanged;

		int m_currentSelection;
		int m_startPosition;
		std::vector<ListBoxItem*> m_items;
		
		GUI::VerticalScrollBar* m_scrollBar;

		ListBox(const ListBox&);
		ListBox& operator = (ListBox&);

	protected:

		virtual void RenderTextToTexture();	
		void OnScroll(System::Event*);		

		virtual void OnMouseLeftButtonDown(System::MouseLeftButtonDownEvent* e);
		virtual void OnMouseWheel(System::MouseWheelEvent* e);
		virtual void OnKeyDown(System::KeyDownEvent* e);

	public:
		ListBox(float x = 0, float y = 0, float width = 0.1, float height = 1, Widget* parent = 0);
		int GetMaxVisibleItems() const;
		void AddItem(ListBoxItem* item);
		void RemoveItem(int position);
		void RemoveItem(ListBoxItem* item);
		void RemoveAllItems();
		int GetItemsCount();
		void InsertItem(ListBoxItem* item, int position);
		int GetCurrentSelection() const { return m_currentSelection; }
		int GetStartOffset() const { return m_startPosition; }
		ListBoxItem* GetItem(int index);
		void SelectItem(int index);
		virtual ~ListBox();
		virtual void Render(IGUIRender* render) const;

		void OnItemChanged(System::Handler e);
	};
}

#endif