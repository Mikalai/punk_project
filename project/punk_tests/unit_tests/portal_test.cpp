#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../../source/punk_engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tests
{
	TEST_CLASS(portal_test)
	{
	public:
		
		TEST_METHOD(PortalCreateTest1)
		{
			Math::Portal::PointsCollection points;
			points.push_back(Math::vec3(1,0,0));
			points.push_back(Math::vec3(1,1,0));
			points.push_back(Math::vec3(0,0,0));

			Math::Portal portal;
			portal.SetPoints(points);

			auto test = portal.GetNormal() - Math::vec3(0, 0, 1);
			test.Chop();
			Assert::IsTrue(test == Math::vec3::Null());
		}

		TEST_METHOD(PortalCreateTest2)
		{
			Math::Portal::PointsCollection points;
			points.push_back(Math::vec3(0,0,0));
			points.push_back(Math::vec3(1,1,0));
			points.push_back(Math::vec3(1,0,0));						

			Math::Portal portal;
			portal.SetPoints(points);

			auto test = portal.GetNormal() - Math::vec3(0, 0, -1);
			test.Chop();
			Assert::IsTrue(test == Math::vec3::Null());
		}
	};
}