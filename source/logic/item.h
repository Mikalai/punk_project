#ifndef _H_PUNK_LOGIC_ITEM
#define _H_PUNK_LOGIC_ITEM

#include "config.h"
#include <memory>

namespace System
{
	class string;
}

namespace Logic
{
	class Item
	{
		class ItemImpl;
		std::auto_ptr<ItemImpl> impl_item;
	public:
		typedef unsigned Integer;		
	public:
		Item();
		Item(const Item& item);
		Item& operator = (const Item& item);

		Integer GetWeight();
		void SetWeight(Integer weight);		

	protected:
		virtual bool IsHangable() const;
		virtual bool IsContainer() const;
		virtual void AddItem(Item& item) = 0;
		virtual void RemoveItem(Item& item) = 0;
	};
}

#endif