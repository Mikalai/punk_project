#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <stdio.h>
#include "..\..\string\string.h"

void f()
{	
	System::string s1(L"Hello world");
	System::string s2(L"Hi Jack! Good day");
	wprintf(L"%s\n", s1.Data());
	for (int i = 0; i < 155; i++)
	{
		s1 = s1 + s2;		
	}

	s1 = s1.Replace(L"Hi", L"HiHiHi");
	std::vector<System::string> s = s1.Split(L" i");

	printf("Usage: %d\nUsing: %d\nAllocs: %d\nFrees: %d\n", System::string::GetTotalMemoryUsed(),
		System::string::GetMemoryUsage(), System::string::GetAllocationsCount(), System::string::GetFreeingCount());

	wprintf(L"s1+s2 = %s\n", s1.Data());
	//		s1.Insert(L'A', 100);		
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	f();
	printf("Usage: %d\nUsing: %d\nAllocs: %d\nFrees: %d\n", System::string::GetTotalMemoryUsed(),
		System::string::GetMemoryUsage(), System::string::GetAllocationsCount(), System::string::GetFreeingCount());
	_CrtDumpMemoryLeaks();
	return 0;
}