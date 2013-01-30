#ifndef _H_PUNK_SYSTEM_ASPECT_ORIENTED_CLASS
#define _H_PUNK_SYSTEM_ASPECT_ORIENTED_CLASS

#include <map>
#include "../errors/module.h"

namespace System
{
	template<class T, typename Key>
	class Aspect
	{
	public:
		typedef std::map<Key, T> Collection;
		typedef typename Collection::iterator iterator;
		typedef typename Collection::const_iterator const_iterator;
	public:

		static T find(const Key& key);
		static iterator _begin();
		static iterator _end();
		static void add(Key key, T value);
		static void invalidate();
		static void validate();
	private:
		static bool m_init;
		static Collection m_items;
	};

	template<class T, typename Key>	
	void Aspect<T, Key>::add(Key key, T value) 
	{ 
		m_items[key]  = value; 
	}

	template<class T, typename Key>	
	inline void Aspect<T, Key>::validate() { m_init = true; }

	template<class T, typename Key>	
	inline void Aspect<T, Key>::invalidate() { m_init = false; }

	template<class T, typename Key>	
	inline T Aspect<T, Key>::find(const Key& key) 
	{ 
		if (!m_init)
			throw PunkNotInitializedException(L"Aspects were not initialized");
		return m_items.find(key)->second; 
	}		
	
	template<class T, typename Key>	
	inline typename Aspect<T, Key>::iterator Aspect<T, Key>::_begin() 
	{ 
		if (!m_init)
			throw PunkNotInitializedException(L"Aspects were not initialized");
		return m_items.begin(); 
	}
	
	template<class T, typename Key>	
	inline typename Aspect<T, Key>::iterator Aspect<T, Key>::_end() 
	{ 
		if (!m_init)
			throw PunkNotInitializedException(L"Aspects were not initialized");
		return m_items.end(); 
	}

	template<class T, typename Key> typename Aspect<T, Key>::Collection Aspect<T, Key>::m_items;
	template<class T, typename Key> bool Aspect<T, Key>::m_init = false;
}

#endif