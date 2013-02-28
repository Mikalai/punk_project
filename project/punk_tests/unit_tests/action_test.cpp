#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../../source/punk_engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tests
{
	TEST_CLASS(ActionTest)
	{
	public:
		
		TEST_METHOD(ActionLoadTest1)
		{
			System::string filename = System::Environment::Instance()->GetModelFolder() + L"male_walk.action";
			Virtual::Action* action =  Cast<Virtual::Action*>(Utility::ParsePunkFile(filename));
		}

		TEST_METHOD(ActionLoadTest2)
		{
			System::string filename = System::Environment::Instance()->GetModelFolder() + L"male_walk.action";
			Virtual::Action* action =  Cast<Virtual::Action*>(Utility::ParsePunkFile(filename));
			Virtual::Animation* animation = Cast<Virtual::Animation*>(action->Find(L"root"));
			Assert::IsTrue(animation != nullptr);
		}

		TEST_METHOD(ActionPositionInterpolationTest3)
		{
			System::string filename = System::Environment::Instance()->GetModelFolder() + L"male_walk.action";
			Virtual::Action* action =  Cast<Virtual::Action*>(Utility::ParsePunkFile(filename));
			Virtual::Animation* animation = Cast<Virtual::Animation*>(action->Find(L"root"));
			Assert::IsTrue(animation != nullptr);

			std::vector<Math::vec3> res;			
			res.push_back(Math::vec3(0,    0.001353f,    0.123324f));
			res.push_back(Math::vec3(0,    0.0012027f,    0.1096213f));    
			res.push_back(Math::vec3(0,    0.0010523f,    0.0959187f));    
			res.push_back(Math::vec3(0,    0.000902f,    0.082216f));    
			res.push_back(Math::vec3(0,    0.0007517f,    0.0685133f));    
			res.push_back(Math::vec3(0,    0.0006013f,    0.0548107f));    
			res.push_back(Math::vec3(0,    0.000451f,    0.041108f));    
			res.push_back(Math::vec3(0,    0.0003007f,    0.0274053f));    
			res.push_back(Math::vec3(0,    0.0001503f,    0.0137027f));        
			res.push_back(Math::vec3(0,    0,    0));            

			for (int i = 0; i < 10; ++i)
			{
				auto v = animation->GetPosition(action->GetStartFrame() + i);
				auto test = v - res[i];
				test = test.Chop();
				Assert::IsTrue(test == Math::vec3::Null());
			}
		}
	};
}