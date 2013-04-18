///*
//	File: SimpleContainer.h
//	Author: Nickolai Abramov
//	Desc: A container nothing to say
//*/
//#ifndef _H_SIMPLE_CONTAINER
//#define _H_SIMPLE_CONTAINER
//
//#define MAX_ELEMENTS 100
//
//#include "../system/system.h"
//#include <vector>
//
//template<class T>
//class SimpleContainer
//{
//	static const int max_elements = 100;
//	T m_elements[max_elements];
//	int cur_element;
//public:
//	SimpleContainer() : cur_element(0)
//	{
//	}
//
//    void Clear()
//    {
//		cur_element = 0;
//    }
//
//    void Add(T element)
//	{
//		if (cur_element > max_elements)
//			throw System::Exception(L"Index out of range in add simple container" + LOG_LOCATION_STRING);
//        m_elements[cur_element++] = element;
//    }
//
//    int Count() const
//    {
//        return cur_element;
//    }
//
//    T operator [] (int index)
//    {
//		if (index >= max_elements)
//			throw System::Exception(L"Index out of range in [] simple container" + LOG_LOCATION_STRING);
//        return m_elements[index];
//    }
//
//    const T operator [] (int index) const
//    {
//		if (index >= max_elements)
//			throw System::Exception(L"Index out of range in [] simple container" + LOG_LOCATION_STRING);
//        return m_elements[index];
//    }
//
//    T At(int index)
//    {
//		if (index >= max_elements)
//			throw System::Exception(L"Index out of range in at simple container" + LOG_LOCATION_STRING);
//        return m_elements[index];
//    }
//
//    const T At(int index) const
//    {
//		if (index >= max_elements)
//			throw System::Exception(L"Index out of range in at simple container" + LOG_LOCATION_STRING);
//        return m_elements[index];
//    }
//};
//
//#endif	//_H_SIMPLE_CONTAINER
