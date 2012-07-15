#ifndef SINGLETONE_H
#define SINGLETONE_H

#define SingletoneImplementation(T)\
namespace T##__private_data\
{\
	T* m_object;\
	T* T##__singletone::Instance()\
    {\
		if (m_object)\
			return m_object;\
		m_object = new T;\
		return m_object;\
	}\
\
	void T##__singletone::Release()\
    {\
		if (m_object)\
			delete m_object;\
	}\
}

#define SingletoneInterface(T, LIB)\
class T;\
namespace T##__private_data\
{\
	extern T* m_object;\
	class LIB T##__singletone\
	{\
	public:\
			static T* Instance();\
        static void Release();\
    };\
}

#define Singletone(T) T##__private_data::T##__singletone

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
