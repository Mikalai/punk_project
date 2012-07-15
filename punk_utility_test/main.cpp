#include <iostream>
#include <stdio.h>
#include "../punk_engine/system/error.h"
#include "../punk_engine/utility/model/punk_scene_loader.h"
#include "../punk_engine/system/environment.h"
#include "../punk_engine/math/mat4.h"
#include "../punk_engine/utility/utility.h"

void animation_test()
{
	Utility::FoodType food;
	food.SetDescription(L"Hello");

	Utility::Scene scene;

	try
	{
		scene.Load(L"mini14_rifle.pmd");		
		scene.PrintDebug();
		Utility::Armature* a = scene.GetArmature(L"Armature");
		a->GetArmatureAnimation().EnableTrack(L"die", true);
		a->GetArmatureAnimation().UpdateBones(10);
		for (int i = 0; i < a->GetBonesCount(); ++i)
		{
			Utility::Bone* b = a->GetBoneByIndex(i);
			std::wcout << b->GetName().Data() << std::endl;
			std::cout << *(&b->GetAnimatedGlobalMatrix()) << std::endl;
		}
		
		System::string outname = System::Environment::Instance()->GetModelFolder() + L"animated_male.armture";
		char buf[2048];
		outname.ToANSI(buf, 2048);
		std::ofstream out(buf, std::ios_base::binary);
		a->Save(out);
		out.close();

		Utility::Armature aa;
		aa.FromFileArmature(outname);

		a = 0;
	}
	catch (System::SystemError& err)
	{
		wprintf(L"%s\n", err.Message().Data());
	}
}

void tree_test()
{
	Utility::Scene scene;
	scene.Load(L"tree_with_lods.pmd");
	Utility::Tree tree;
	tree.MakeFromScene(scene);

	std::ofstream stream(L"tree.ugeom");
	tree.Save(stream);
	Utility::LodContainer& c = tree.GetTrunkLods();
}

int main()
{
	animation_test();
	return 0;
}