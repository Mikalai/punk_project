#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <stdio.h>
#include "../punk_engine/math/math.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Math::quat q = Math::quat::FromAngleAxis(Math::PI/6, Math::vec3(0, 0, 1));
	q.W() = 0.7;
	q.Z() = 0.7;

	wprintf(L"%s\n", q.ToString().Data());
	q.Normalize();
	wprintf(L"%s\n", q.ToString().Data());
	Math::mat4 m = q.ToMatrix4x4();
	wprintf(L"\n%s\n", m.ToString().Data());

	/*
	Math::vec3 v(1, 0, 0);
	wprintf(L"%s\n", q.Rotate(v).ToString().Data());
	Math::mat4 m = q.ToMatrix4x4();
	wprintf(L"%s\n", (m * v.ToHomogeneous()).ToString().Data());*/
	_CrtDumpMemoryLeaks();
	
	return 0;
}