/// NOT NOW
#ifndef _H_PUNK_GUI_LAYOUT
#define _H_PUNK_GUI_LAYOUT

#include <memory>

namespace Math
{
	template<class T> class Vector2;
}

namespace GUI
{
	class Widget;

	class Layout
	{
		struct LayoutImpl;
		std::auto_ptr<LayoutImpl> impl_layout;
	public:
		Layout();
		Layout(const Layout& layout);
		Layout& operator = (const Layout& layout);
		virtual ~Layout();

		void AddWidget(Widget* widget);
		void SetParent(Widget* parent);

		unsigned GetItemCount();

		const Vector2<float>& GetPosition(
		
		virtual unsigned GetOptimalWidth() = 0;
		virtual unsigned GetOptimalHeight() = 0;

		bool Save(System::Buffer& buffer) const;
		bool Load(System::Buffer& buffer);		
	};
}

#endif