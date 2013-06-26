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
        static void remove(T value);
        static void remove(Key value);
		static void invalidate();
		static void validate();
		static void clear();
	private:
		static bool m_init;
		static Collection m_items;
	};

	template<class T, typename Key>	
	void Aspect<T, Key>::add(Key key, T value) 
	{ 
        if (m_items.find(key) != m_items.end())
            throw PunkInvalidArgumentException(L"Item already in collection");
		m_items[key]  = value; 
	}

    template<class T, typename Key>
    void Aspect<T, Key>::remove(T value)
    {
        auto it = m_items.begin();
        while (it != m_items.end())
        {
            if (it->second == value)
            {
                delete it->second;
                m_items.erase(it);
                break;
            }
            ++it;
        }
    }

    template<class T, typename Key>
    void Aspect<T, Key>::remove(Key value)
    {
        auto it = m_items.find(value);
        if (it != m_items.end())
            m_items.erase(it);
    }

	template<class T, typename Key>	
	void Aspect<T, Key>::clear()
	{ 
		m_items.clear();
	}

	template<class T, typename Key>	
	inline void Aspect<T, Key>::validate() { m_init = true; }

	template<class T, typename Key>	
	inline void Aspect<T, Key>::invalidate() { m_init = false; }

	template<class T, typename Key>	
    inline T Aspect<T, Key>::find(const Key& key)
	{ 
//		if (!m_init)
//			throw PunkNotInitializedException(L"Aspects were not initialized");
		typename Collection::iterator it = m_items.find(key);
		if (it != m_items.end())
			return it->second; 
        return T(0);
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

#endif	//	_H_PUNK_SYSTEM_ASPECT_ORIENTED_CLASS
