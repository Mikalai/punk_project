#include <iostream>
#include <stdio.h>
#include "../punk_engine/system/error.h"
#include "../punk_engine/utility/model/punk_scene_loader.h"
#include "../punk_engine/system/environment.h"
#include "../punk_engine/math/mat4.h"

int main()
{
	Utility::Scene scene;

	try
	{
		scene.Load(L"animated_male2.pmd");		
		Utility::Armature* a = scene.GetArmature(L"Armature");
		a->GetArmatureAnimation().EnableTrack(L"die", true);
		a->GetArmatureAnimation().UpdateBones(10);
		for (int i = 0; i < a->GetBonesCount(); ++i)
		{
			Utility::Bone* b = a->GetBoneByIndex(i);
			std::wcout << b->GetName().Data() << std::endl;
			std::cout << *(&b->GetAnimatedGlobalMatrix()) << std::endl;
		}

		a = 0;
	}
	catch (System::SystemError& err)
	{
		wprintf(L"%s\n", err.Message());
	}

	return 0;
}