#ifndef _H_PUNK_SYSTEM_POINTER_PROXY
#define _H_PUNK_SYSTEM_POINTER_PROXY

#include <assert.h>
#include "../types/base_types.h"
#include "../concurrency/atomic.h"

namespace System
{
	template<class T> 
	class Proxy
	{
		struct Impl
		{
			T* m_data;
			System::int32 m_count;

			Impl(T* data) : m_data(data), m_count(1) {}
			Impl() : m_data(new T), m_count(1) {}
			Impl(const Impl& impl) : m_data(new T(impl.m_data)), m_count(1) {}
			~Impl() { delete m_data; }
		};

		mutable Impl* m_impl;

	public:

		Proxy() : m_impl(0) {}
		
		explicit Proxy(T* data) : m_impl(0)
		{
			if (data)
				m_impl = new Impl(data);
		}

		template<class U>
		explicit Proxy(U* data)
		{
			if (data)
				m_impl = new Impl(data);
		}

		Proxy(const Proxy<T>& v)
		{		
			m_impl = v.m_impl;
			if (m_impl)
				System::AtomicIncrement32(&m_impl->m_count);
		}

		template<class U>
		Proxy(const Proxy<U>& v)
		{	
			if (v.m_impl != nullptr)
			{
				const T* flag = dynamic_cast<const T*>(v.m_impl->m_data);
				if (flag)
				{
					m_impl = (Impl*)(v.m_impl);
					if (m_impl)
						System::AtomicIncrement32(&m_impl->m_count);
				}
				else
					m_impl = 0;
			}
		}

		Proxy<T>& operator = (const Proxy<T>& v)
		{		
			Proxy<T> temp(v);
			std::swap(temp.m_impl, m_impl);
			return *this;
		}

		template<class U>
		Proxy<T>& operator = (const Proxy<U>& v)
		{
			if (v.m_impl->m_data != nullptr)
			{
				const T* flag = dynamic_cast<T*>(v.m_impl->m_data);
				if (flag)
				{
					Proxy<T> temp(v);
					std::swap(temp.m_impl, m_impl);
					return *this;
				}				
				out_warning() << "Can't convert types from " << typeid(U).name() << " to " << typeid(T).name() << std::endl;
			}
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
				Release();
				m_impl = new Impl(data);				
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
			if (m_impl && System::AtomicDecrement32(&m_impl->m_count) == 0)
			{	
				delete m_impl; 				
			}
			m_impl = 0;
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
		
		const T* operator -> () const
		{ 
			assert(m_impl);
			return m_impl->m_data; 
		}

		operator T* () 
		{
			assert(m_impl);
			return m_impl->m_data;		
		}

		operator const T* () const
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

		T* Get()
		{
			assert(m_impl);
			return m_impl->m_data;
		}

		const T* Get() const
		{
			assert(m_impl);
			return m_impl->m_data;
		}

		template<class U>
		friend class Proxy;
	};
}

#endif	//	_H_PUNK_SYSTEM_POINTER_PROXY