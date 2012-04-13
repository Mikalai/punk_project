#include <stdio.h>
#include "../punk_engine/system/error.h"
#include "../punk_engine/utility/model/punk_scene_loader.h"
#include "../punk_engine/system/environment.h"

int main()
{
	Utility::Scene scene;

	try
	{
		scene.Load(L"animated_male2.pmd");
	}
	catch (System::SystemError& err)
	{
		wprintf(L"%s\n", err.Message());
	}

	return 0;
}