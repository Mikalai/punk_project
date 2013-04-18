//#include <iostream>
//#include "property_collection.h"
//#include <iterator>
//
//namespace Logic
//{
//	PropertyCollection::PropertyCollection()
//	{
//		//std::cout << __FUNCSIG__ << std::endl;
//	}
//
//	PropertyCollection::PropertyCollection(const PropertyCollection& p)
//		: m_collection(p.begin(), p.end())
//	{
//		//std::cout << __FUNCSIG__ << std::endl;
//	}
//
//	PropertyCollection& PropertyCollection::operator = (const PropertyCollection& p)
//	{
//		//std::cout << __FUNCSIG__ << std::endl;
//		if (this != &p)
//		{
//			m_collection.clear();
//			m_collection.insert(p.begin(), p.end());
//		}
//		return *this;
//	}
//
//	Property* PropertyCollection::RegisterProperty(ID value)
//	{
//		return &(m_collection[value] = Property(value));
//	}
//
//	void PropertyCollection::UnregisterProperty(ID value)
//	{
//		iterator it = m_collection.find(value);
//		if (m_collection.end() != it)
//			m_collection.erase(it);
//	}
//
//	Property* PropertyCollection::GetProperty(ID value)
//	{
//		iterator it = m_collection.find(value);
//		if (m_collection.end() != it)
//			return &it->second;
//		return 0;
//	}
//
//	PropertyCollection::iterator PropertyCollection::begin()
//	{
//		return m_collection.begin();
//	}
//
//	PropertyCollection::const_iterator PropertyCollection::begin() const
//	{
//		return m_collection.begin();
//	}
//
//	PropertyCollection::iterator PropertyCollection::end()
//	{
//		return m_collection.end();
//	}
//
//	PropertyCollection::const_iterator PropertyCollection::end() const
//	{
//		return m_collection.end();
//	}
//
//	Property& PropertyCollection::operator[] (ID name)
//	{
//		return m_collection[name];
//	}
//
//	const Property& PropertyCollection::operator[] (ID name) const
//	{
//		return m_collection.at(name);
//	}
//
//	bool PropertyCollection::HasProperty(ID name)
//	{
//		return m_collection.find(name) != m_collection.end();
//	}
//}
