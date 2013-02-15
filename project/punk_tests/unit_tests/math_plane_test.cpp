#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../../source/punk_engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tests
{		
	TEST_CLASS(MathPlaneTest)
	{
	public:
		
		TEST_METHOD(CheckPlaneConstructor)
		{
			Math::Plane p;
			p.Set(Math::vec3(0,0,0), Math::vec3(1,0,0), Math::vec3(0,1,0));				 
			if (p.GetNormal() != Math::vec3(0,0,1))
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(L"Bad normal");
		}

	};
}