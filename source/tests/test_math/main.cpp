#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <stdio.h>
#include "../../punk_engine.h"

void Test1()
{
	Math::mat3 m;
	m[0] = 3.0f / 2.0f;
	m[1] = 1.0f / 2.0f;
	m[2] = 3.0f / 4.0f;
	m[3] = 1.0f / 2.0f;
	m[4] = 1.0f / 2.0f;
	m[5] = 1.0f / 4.0f;
	m[6] = 3.0f / 4.0f;
	m[7] = 1.0f / 4.0f;
	m[8] = 1.0f / 2.0f;

	Math::mat3 mm;
	Math::DiagonalizeMatrix(m, mm);
	out_message() << std::endl << m.ToString() << std::endl;
	out_message() << std::endl << mm.ToString() << std::endl;

	Math::vec3 v;
	Math::vec3 res[3];
	Math::EigenValues(m, v);
	Math::EigenVectors(m, v, res);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Test1();

	_CrtDumpMemoryLeaks();
	
	return 0;
}