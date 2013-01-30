#ifndef _H_PUNK_SYSTEM_POINTER_PROXY
#define _H_PUNK_SYSTEM_POINTER_PROXY

#include <assert.h>
#include <algorithm>
#include "../types/base_types.h"
#include "../concurrency/atomic.h"

namespace System
{
	/*class RefCountBase
	{
	protected:
		RefCountBase() : m_count(1)
		{}

	protected:

		virtual void Delete() = 0;
		virtual void DeleteThis() = 0;

		bool IncRef()
		{
			for (;;)
			{
				unsigned long temp = static_cast<volatile unsigned long&>(m_count);			
				if (temp == 0)
					return false;
				if (_InterlockedCompareExchange(&m_count, temp+1, temp) == temp)
					return true;
			}
		}

		unsigned DecRef()
		{
			if (_InterlockedDecrement(&m_count) == 0)
			{
				Delete();
				DeleteThis();
			}
		}

		unsigned long GetCount()
		{
			return m_count;
		}

	private:
		unsigned long m_count;
	};

	template<class T>
	class RefCount : public RefCountBase
	{
	public:
	protected:
		
		RefCount(T* data) : m_ptr(data) {}

		virtual void Destroy()
		{
			delete m_ptr;
		}

		virtual void DestroyThis()
		{
			delete this;
		}

	private:
		T* m_ptr;
	};*/

	template<class T> 
	class Proxy
	{		
	public:

		Proxy() : m_ptr(0), m_count(0) {}
		
		explicit Proxy(T* data) 			
		{
			if (data)
			{
				m_ptr = data;
				m_count = new uint32(1);
			}
		}

		template<class U>
		explicit Proxy(U* data)
		{
			if (data)
			{
				m_ptr = data;
				m_count = new uint32(1);
			}
		}

		Proxy(const Proxy<T>& v)
		{		
			v.IncRef();
			m_ptr = v.m_ptr;			
			m_count = v.m_count;			
		}

		template<class U>
		Proxy(const Proxy<U>& v)
		{		
			T* value = dynamic_cast<T*>(v.m_ptr);
			if (value)
			{
				v.IncRef();
				m_ptr = value;
				m_count = v.m_count;			
			}
		}

		template<class U>
		Proxy<U> As()
		{
			U* value = dynamic_cast<U*>(m_ptr);
			if (value)
			{
				IncRef();
				Proxy<U> result;
				result.m_ptr = value;
				result.m_count = m_count;
				return result;
			}
			return Proxy<U>(0);
		}

		template<class U>
		const Proxy<U> As() const
		{
			U* value = dynamic_cast<U*>(m_ptr);
			if (value)
			{
				IncRef();
				Proxy<U> result;
				result.m_ptr = value;
				result.m_count = m_count;
				return result;
			}
			return Proxy<U>(0);
		}

		Proxy<T>& operator = (const Proxy<T>& v)
		{		
			v.IncRef();
			m_ptr = v.m_ptr;
			m_count = v.m_count;
			return *this;
		}

		template<class U>
		Proxy<T>& operator = (const Proxy<U>& v)
		{					
			//	increase ref count, it means no one will be able physicaly destroy object
			v.IncRef();
			//	perform cast
			T* value = dynamic_cast<T*>(v.m_ptr);			
			if (value)
			{				
				//	if ok, release current resource
				Release();				
				//	assign new resource
				m_ptr = value;
				//	count already incremented
				m_count = v.m_count;
			}
			else
			{
				//	if impossible to assign, decrease increase ref count
				v.DecRef();
			}
			return *this;
		}

		~Proxy() 
		{ 
			Release();
		}

		void Reset(T* data)
		{				
			if (m_ptr)
			{
				Release();
			}
			m_ptr = data;
			m_count = new uint32(1);
		}

		bool IncRef() const
		{
			if (!m_count)
				return false;

			for (;;)
			{
				uint32 temp = static_cast<volatile uint32&>(*m_count);
				if (temp == 0)
					return false;

				if (System::AtomicCompareExchange(reinterpret_cast<volatile int32*>(m_count), (int32)temp+1, (int32)temp) == temp)
					return true;
			}
		}

		void DecRef() const
		{
			if (m_ptr && System::AtomicDecrement32(reinterpret_cast<volatile int32*>(m_count)) == 0)
			{	
				delete m_ptr; 								
				delete m_count;				
				m_ptr = 0; 								
				m_count = 0;				
			}			
		}

		void Release()
		{		
			DecRef();
			m_ptr = 0;
			m_count = 0;
		}

		bool IsValid() const
		{
			return m_ptr != nullptr;
		}

		T* operator -> () 
		{ 
			assert(m_ptr);
			return m_ptr;
		}
		
		const T* operator -> () const
		{ 
			assert(m_ptr);
			return m_ptr;
		}

		operator T* () 
		{
			assert(m_ptr);
			return m_ptr;
		}

		operator const T* () const
		{
			assert(m_ptr);
			return m_ptr;
		}

		uint32 GetCount() const
		{
			if (m_count)
				return *m_count;
			return 0;
		}

		//void SetData(T* data)
		//{
		//	assert(m_impl);
		//	delete m_impl->m_data;
		//	m_impl->m_data = data;
		//}

		T* Get()
		{
			assert(m_ptr);
			return m_ptr;
		}

		const T* Get() const
		{
			assert(m_ptr);
			return m_ptr;
		}

	private:
		mutable T* m_ptr;
		volatile mutable System::uint32* m_count;

		template<class U>
		friend class Proxy;
	};
}

#endif	//	_H_PUNK_SYSTEM_POINTER_PROXY