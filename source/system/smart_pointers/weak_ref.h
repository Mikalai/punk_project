//#ifndef _H_HANDLE
//#define _H_HANDLE
//
//#include "proxy.h"
//
//namespace System
//{
//	template<class T>
//	class WeakRef
//	{
//		Proxy<T>& m_handle;
//	public:
//		WeakRef(Proxy<T>& handle) : m_handle(handle) {}
//		WeakRef(const WeakRef<T>& value) : m_handle(value.m_handle) {}			
//
//		operator Proxy<T>& () { return m_handle; }
//		Proxy<T>& operator -> () { return m_handle; }
//
//		bool IsValid() const { return m_handle.IsValid(); }
//	};
//
//	//template<class T>
//	//class Handle_on_auto_ptr
//	//{
//	//	std::auto_ptr<T>& m_handle;
//	//public:
//	//	Handle_on_auto_ptr(std::auto_ptr<T>& value) : m_handle(value) {}	
//	//	Handle_on_auto_ptr(const Handle_on_auto_ptr<T>& value) : m_handle(value.m_handle) {}	
//	//
//	//	Handle_on_auto_ptr<T>& operator = (const Handle_on_auto_ptr<T>& value)
//	//	{
//	//		Handle_on_auto_ptr<T> temp(value);
//	//		std::swap(temp.m_handle, m_handle);
//	//		return *this;
//	//	}
//	//
//	//	operator std::auto_ptr<T>& () { return m_handle; }
//	//	std::auto_ptr<T>& operator -> () { return m_handle; }
//	//};
//}
//
//#endif