#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <iostream>
#include "..\..\system\system.h"

struct Object
{
	char buf[2048];
};

void TestStdList()
{
	std::list<Object> list;

	for (int i = 0; i < 10; i++)
		list.push_back(Object());
}

void TestList()
{
	System::List<Object> list;

	for (int i = 0; i < 10; i++)
		list.PushBack(Object());

	//for (auto it = list.Begin(); it != list.End(); ++it)
	//{
	//	int k = *it;

	//	std::cout << k << std::endl;
	//}
}

void CompareLists()
{
	System::Profiler p;

	p.Start(L"Punk list");
	TestList();
	p.End();
	out_message() << p.ToString() << std::endl;
	
	p.Start(L"STD list");
	TestStdList();
	p.End();
	out_message() << p.ToString() << std::endl;

	p.Start(L"Punk list");
	TestList();
	p.End();
	out_message() << p.ToString() << std::endl;
}

void TestList2()
{
	System::List<int> l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushFront(0);
	l1.PushFront(-1);

	for (auto it = l1.Begin(); it != l1.End(); ++it)
	{
		int k = *it;

		std::cout << k << std::endl;
	}

	System::List<int> l2;
	l2.PushBack(6);
	l2.PushBack(7);

	l1.Join(l1.Begin(), l2);
	for (auto it = l1.Begin(); it != l1.End(); ++it)
	{
		int k = *it;

		std::cout << k << std::endl;
	}

	System::List<int> l3;
	l1.Clone(l3);
	
	for (auto it = l3.Begin(); it != l3.End(); ++it)
	{
		int k = *it;

		std::cout << k << std::endl;
	}
}

struct Cmp
{
	bool operator () (int a, int b)
	{
		return a < b; 
	}
};

void TestPList()
{
	System::priority_list<int, Cmp> lst;
	lst.insert(5);
	lst.insert(2);
	lst.insert(3);

	for each (auto e in lst)
	{
		std::cout << e << std::endl;
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(177);

	TestPList();
	
	return 0;
}