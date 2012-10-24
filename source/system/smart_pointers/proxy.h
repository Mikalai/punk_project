#ifndef _H_PUNK_SYSTEM_POINTER_PROXY
#define _H_PUNK_SYSTEM_POINTER_PROXY

#include <assert.h>

namespace System
{
	template<class T> 
	class Proxy
	{
		struct Impl
		{
			T* m_data;
			int m_count;

			Impl(T* data) : m_data(data), m_count(1) {}
			Impl() : m_data(new T), m_count(1) {}
			Impl(const Impl& impl) : m_data(new T(impl.m_data)), m_count(1) {}
			~Impl() { delete m_data; }
		};

		Impl* m_impl;

	public:

		Proxy() : m_impl(0) {}

		Proxy(T* data) : m_impl(0)
		{
			if (data)
				m_impl = new Impl(data);
		}

		Proxy(const Proxy<T>& v)
		{		
			m_impl = v.m_impl;
			if (m_impl)
				m_impl->m_count++;
		}

		Proxy<T>& operator = (const Proxy<T>& v)
		{		
			Proxy<T> temp(v);
			std::swap(temp.m_impl, m_impl);
			return *this;
		}

		~Proxy() 
		{ 
			Release();
		}

		void Reset(T* data)
		{				
			if (m_impl)
			{
				delete m_impl->m_data;
				m_impl->m_data = data;
			}
			else
				m_impl = new Impl(data);
		}

		void AddRef()
		{
			assert(m_impl);
			++m_impl->m_count;
		}

		void Release()
		{		
			if (m_impl && --m_impl->m_count == 0)
			{	
				delete m_impl; 
				m_impl = 0;
			}
		}

		bool IsValid() const
		{
			return m_impl && m_impl->m_data;
		}

		T* operator -> () 
		{ 
			assert(m_impl);
			return m_impl->m_data; 
		}

		operator T* () 
		{
			assert(m_impl);
			return m_impl->m_data;		
		}

		int GetCount() const
		{
			if (m_impl)
				return m_impl->m_count;
			return 0;
		}

		void SetData(T* data)
		{
			assert(m_impl);
			delete m_impl->m_data;
			m_impl->m_data = data;
		}
	};
}

#endif	//	_H_PUNK_SYSTEM_POINTER_PROXY