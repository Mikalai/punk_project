#ifndef _H_REF_COUNT
#define _H_REF_COUNT

template<class T> 
class RefCount
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

	RefCount() : m_impl(0) {}
	
	RefCount(T* data) : m_impl(0)
	{
		if (data)
			m_impl = new Impl(data);
	}

	RefCount(const RefCount<T>& v)
	{		
		m_impl = v.m_impl;
		if (m_impl)
			m_impl->m_count++;
	}

	RefCount<T>& operator = (const RefCount<T>& v)
	{		
		RefCount<T> temp(v);
		std::swap(temp.m_impl, m_impl);
		return *this;
	}

	~RefCount() 
	{ 
		Release();
	}

	void Reset(T* data)
	{				
		Release();
		if (data)
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

	bool IsValid()
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
};

#endif