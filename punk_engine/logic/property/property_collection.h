#ifndef _H_PROPERTY_COLLECTION
#define _H_PROPERTY_COLLECTION

#include <map>
#include "../config.h"
#include "property.h"

namespace Logic
{
	class PUNK_LOGIC_MODULE PropertyCollection
	{
		struct Compare
		{
			bool operator () (const char* a, const char* b) const
			{
				return strcmp(a, b) == -1;
			}
		};

		typedef std::map<ID, Property> type;
		typedef type::iterator iterator;
		typedef type::const_iterator const_iterator;
		type m_collection;
	public:
		PropertyCollection();
		PropertyCollection(const PropertyCollection& p);
		PropertyCollection& operator = (const PropertyCollection& p);

		Property* RegisterProperty(ID name);
		void UnregisterProperty(ID name);

		Property* GetProperty(ID name);

		Property& operator[] (ID name);
		const Property& operator[] (ID name) const;

		bool HasProperty(ID name);

		iterator begin();
		const_iterator begin() const;
		iterator end(); 
		const_iterator end() const;
	};
}
#endif