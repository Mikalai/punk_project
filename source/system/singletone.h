#ifndef SINGLETONE_H
#define SINGLETONE_H

#include <memory>
#include "mega_destroyer.h"

//#define SingletoneImplementation(T)\
//	std::unique_ptr<T> T::m_instance;\
//	T* T::Instance()\
//	{\
//		if (!m_instance.get())\
//		{\
//			m_instance.reset(new T);\
//			System::MegaDestroyer::Instance()->PushDestroyer(Destroy);\
//		}\
//		return m_instance.get();\
//	}\
//	void T::Destroy()\
//	{\
//		m_instance.reset(nullptr);\
//	}
//
//
//#define SingletoneInterface(T)\
//private:\
//	static std::unique_ptr<T> m_instance;\
//public:	\
//	static T* Instance();\
//	static void Destroy();

	/*
    template<class T>
    class Singletone
    {
	private:
		//Singletone();
        //Singletone(const Singletone&);
        static T* m_object;
    public:

        static T* Instance()
        {
            //
            //  add synchronization here
            //
            if (m_object)
                return m_object;
            m_object = new T;

			return m_object;
        }

        static void Release()
        {
            if (m_object)
                delete m_object;
        }
    };

    template<class T> extern T* Singletone<T>::m_object = 0;/**/

#endif // SINGLETONE_H
