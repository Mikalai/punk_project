#ifndef _H_PUNK_SYSTEM_TEMPLATE_SINGLETONE
#define _H_PUNK_SYSTEM_TEMPLATE_SINGLETONE

#include <memory>

namespace System
{
	template<class T>
	class Singletone
	{
		static std::auto_ptr<T> m_instance;
	public:

		static T* Instance() 
		{
			if (!m_instance.get())
				m_instance.reset(new T);
			return m_instance.get();
		}

		static void Destroy()
		{
			m_instance.reset(0);
		}
	};

	template<class T> std::auto_ptr<T> Singletone<T>::m_instance;
}

#endif