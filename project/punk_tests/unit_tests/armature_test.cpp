#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../../source/punk_engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tests
{
	TEST_CLASS(armature_test)
	{
	public:
		
		TEST_METHOD(AramtureLoadFromTextFileTest1)
		{
			System::string filename = System::Environment::Instance()->GetModelFolder() + L"male_armature.armature";
			Virtual::HumanMaleArmature* armature = Cast<Virtual::HumanMaleArmature*>(Utility::ParsePunkFile(filename));
		}

	};
}