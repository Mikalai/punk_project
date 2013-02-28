#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../../source/punk_engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_tests
{
	TEST_CLASS(bbox_test)
	{
	public:
		
		TEST_METHOD(CovarianceMatrixTest1)
		{
			std::vector<Math::vec3> points;
			points.push_back(Math::vec3(-1, -2, 1));
			points.push_back(Math::vec3( 1,  0, 2));
			points.push_back(Math::vec3( 2, -1, 3));
			points.push_back(Math::vec3( 2, -1, 2));

			Math::mat3 m = CreateCovarianceMatrix(points[0], points.size(), sizeof(Math::vec3));
			Math::mat3 test = Math::mat3(3.0f/2.0f, 1.0f / 2.0f, 3.0f / 4.0f, 1.0f / 2.0f, 1.0f / 2.0f, 1.0f / 4.0f, 3.0f / 4.0f, 1.0f / 4.0f, 1.0f / 2.0f);
			auto mm = m - test;
			mm.Chop();
			auto flag = mm == Math::mat3::Null();
			//for (int i = 0; i < 9; ++ i)
			//{
			//	if (mm[i] != 0.0f)
			//	{
			//		flag = false;
			//		break;
			//	}
			//}
			Assert::IsTrue(flag);
		}

		TEST_METHOD(CovarianceMatrixTest2)
		{
			std::vector<Math::vec3> points;
			points.push_back(Math::vec3(0, 0, 0));

			Math::mat3 m = CreateCovarianceMatrix(points[0], points.size(), sizeof(Math::vec3));
			Math::mat3 test = Math::mat3(0,0,0,
				0,0,0,
				0,0,0);

			auto mm = m - test;
			mm.Chop();
			auto flag = mm == Math::mat3::Null();
			Assert::IsTrue(flag);
		}

		TEST_METHOD(CovarianceMatrixTest3)
		{
			std::vector<Math::vec3> points;
			points.push_back(Math::vec3(0, 0, 0));
			points.push_back(Math::vec3(1, 0, 0));

			Math::mat3 m = CreateCovarianceMatrix(points[0], points.size(), sizeof(Math::vec3));
			Math::mat3 test = Math::mat3(0.25f,0,0,
				0,0,0,
				0,0,0);

			auto mm = m - test;
			mm.Chop();
			auto flag = mm == Math::mat3::Null();
			Assert::IsTrue(flag);
		}

		TEST_METHOD(CovarianceMatrixTest4)
		{
			std::vector<Math::vec3> points;
			points.push_back(Math::vec3(1, 0, 0));
			points.push_back(Math::vec3(1, 0, 0));

			Math::mat3 m = CreateCovarianceMatrix(points[0], points.size(), sizeof(Math::vec3));
			Math::mat3 test = Math::mat3(0,0,0,
				0,0,0,
				0,0,0);

			auto mm = m - test;
			mm.Chop();
			auto flag = mm == Math::mat3::Null();
			Assert::IsTrue(flag);
		}

		TEST_METHOD(CovarianceMatrixTest5)
		{
			std::vector<Math::vec3> points;
			points.push_back(Math::vec3(0, 1, 0));
			points.push_back(Math::vec3(1, 0, 0));

			Math::mat3 m = CreateCovarianceMatrix(points[0], points.size(), sizeof(Math::vec3));
			Math::mat3 test = Math::mat3(0.25f, -0.25, 0,
				-0.25, 0.25, 0,
				0,0,0);

			auto mm = m - test;
			mm.Chop();
			auto flag = mm == Math::mat3::Null();
			Assert::IsTrue(flag);
		}

		TEST_METHOD(CovarianceMatrixTest6)
		{
			std::vector<Math::vec3> points;
			points.push_back(Math::vec3(0, 1, 0));
			points.push_back(Math::vec3(1, 0, 0));
			points.push_back(Math::vec3(0, 0, 1));

			Math::mat3 m = CreateCovarianceMatrix(points[0], points.size(), sizeof(Math::vec3));
			Math::mat3 test = Math::mat3(0.2222222f, -0.1111111, -0.1111111,
				-0.1111111, 0.2222222, -0.1111111,
				-0.1111111, -0.111111, 0.2222222);

			auto mm = m - test;
			mm.Chop();
			auto flag = mm == Math::mat3::Null();
			Assert::IsTrue(flag);
		}

		TEST_METHOD(CovarianceMatrixTest7)
		{
			std::vector<Math::vec3> points;
			points.push_back(Math::vec3(-1, -1, -1));
			points.push_back(Math::vec3(-1, -1, 1));
			points.push_back(Math::vec3(-1, 1, -1));
			points.push_back(Math::vec3(-1, 1, 1));
			points.push_back(Math::vec3(1, -1, -1));
			points.push_back(Math::vec3(1, -1, 1));
			points.push_back(Math::vec3(1, 1, -1));
			points.push_back(Math::vec3(1, 1, 1));

			Math::mat3 m = CreateCovarianceMatrix(points[0], points.size(), sizeof(Math::vec3));
			Math::mat3 test = Math::mat3(1, 0, 0,
				0, 1, 0,
				0, 0, 1);

			auto mm = m - test;
			mm.Chop();
			auto flag = mm == Math::mat3::Null();
			Assert::IsTrue(flag);
		}

		TEST_METHOD(EigenValuesTest1)
		{
			Math::mat3 m = Math::mat3(3.0f/2.0f, 1.0f / 2.0f, 3.0f / 4.0f, 1.0f / 2.0f, 1.0f / 2.0f, 1.0f / 4.0f, 3.0f / 4.0f, 1.0f / 4.0f, 1.0f / 2.0f);
			Math::vec3 v;
			Math::EigenValues(m, v);

			Math::vec3 res(2.0969388f, 0.3054980f, 0.0975632f);

			auto t = res - v;
			t.Chop(0.0001);
			bool flag = t == Math::vec3::Null();
			Assert::IsTrue(flag);
		}

		TEST_METHOD(EigenValuesTest2)
		{
			Math::mat3 m = Math::mat3(1, 0, 0,
				0, 1, 0,
				0, 0, 1);

			Math::vec3 v;
			Math::EigenValues(m, v);

			Math::vec3 res(1, 1, 1);

			auto t = res - v;
			t.Chop(0.0001);
			bool flag = t == Math::vec3::Null();
			Assert::IsTrue(flag);
		}

		TEST_METHOD(EigenVectorsTest1)
		{
			Math::mat3 m = Math::mat3(3.0f/2.0f, 1.0f / 2.0f, 3.0f / 4.0f, 1.0f / 2.0f, 1.0f / 2.0f, 1.0f / 4.0f, 3.0f / 4.0f, 1.0f / 4.0f, 1.0f / 2.0f);
			Math::vec3 vectors[3];
			Math::vec3 values(2.0969388f, 0.3054980f, 0.0975632f);
			Math::EigenVectors(m, values, vectors);			

			Math::vec3 v1(-0.8333967, -0.3303048, -0.4431126);
			Math::vec3 v2(-0.2573420, 0.9414602, -0.2177793);
			Math::vec3 v3(0.4891064, -0.0674651, -0.8696111);			

			//	it is consodered that eigen vectors are the same if they have equal length and collinear
			//	but their direction may differ. I'm not quite sure is that ok !!!!!!

			float eps = 0.0001;
			bool f1 = Math::Abs(Math::Abs(v1.Dot(vectors[0])) - 1.0f) < eps;
			bool f2 = Math::Abs(Math::Abs(v2.Dot(vectors[1])) - 1.0f) < eps;
			bool f3 = Math::Abs(Math::Abs(v3.Dot(vectors[2])) - 1.0f) < eps;
			
			bool flag = f1 && f2 && f3;

			Assert::IsTrue(flag);
		}

		TEST_METHOD(EigenVectorsTest3)
		{
			Math::mat3 m = Math::mat3(3.0f/2.0f, 1.0f / 2.0f, 3.0f / 4.0f, 1.0f / 2.0f, 1.0f / 2.0f, 1.0f / 4.0f, 3.0f / 4.0f, 1.0f / 4.0f, 1.0f / 2.0f);
			Math::vec3 vectors[3];
			Math::vec3 v;
			Math::vec3 values(2.0969388f, 0.3054980f, 0.0975632f);

			Math::vec3 v1(-0.8333967, -0.3303048, -0.4431126);
			Math::vec3 v2(-0.2573420, 0.9414602, -0.2177793);
			Math::vec3 v3(0.4891064, -0.0674651, -0.8696111);			

			Math::mat3 r;
			Math::SymmetricEigenSystem(m, v, r);

			vectors[0].Set(r.At(0,0), r.At(1, 0), r.At(2, 0));
			vectors[1].Set(r.At(0,1), r.At(1, 1), r.At(2, 1));
			vectors[2].Set(r.At(0,2), r.At(1, 2), r.At(2, 2));

			//	it is consodered that eigen vectors are the same if they have equal length and collinear
			//	but their direction may differ. I'm not quite sure is that ok !!!!!!

			float eps = 0.0001;
			float t1 = Math::Abs(v1.Dot(vectors[0]));
			float t2 = Math::Abs(v2.Dot(vectors[1]));
			float t3 = Math::Abs(v3.Dot(vectors[2]));
			bool f1 = Math::Abs(t1 - 1.0f) < eps;
			bool f2 = Math::Abs(t2 - 1.0f) < eps;
			bool f3 = Math::Abs(t3 - 1.0f) < eps;
			
			bool flag = f1 && f2 && f3;

			Assert::IsTrue(flag);
		}

		TEST_METHOD(EigenVectorsTest4)
		{
			Math::mat3 m = Math::mat3(1, 0, 0,
				0, 1, 0,
				0, 0, 1);

			Math::vec3 vectors[3];
			Math::vec3 v;
			Math::vec3 values(1, 1, 1);

			Math::vec3 v1(1, 0, 0);
			Math::vec3 v2(0, 1, 0);
			Math::vec3 v3(0, 0, 1);	

			Math::mat3 r;
			Math::SymmetricEigenSystem(m, v, r);

			vectors[0].Set(r.At(0,0), r.At(1, 0), r.At(2, 0));
			vectors[1].Set(r.At(0,1), r.At(1, 1), r.At(2, 1));
			vectors[2].Set(r.At(0,2), r.At(1, 2), r.At(2, 2));

			//	it is consodered that eigen vectors are the same if they have equal length and collinear
			//	but their direction may differ. I'm not quite sure is that ok !!!!!!

			float eps = 0.0001;
			float t1 = Math::Abs(v1.Dot(vectors[0]));
			float t2 = Math::Abs(v2.Dot(vectors[1]));
			float t3 = Math::Abs(v3.Dot(vectors[2]));
			bool f1 = Math::Abs(t1 - 1.0f) < eps;
			bool f2 = Math::Abs(t2 - 1.0f) < eps;
			bool f3 = Math::Abs(t3 - 1.0f) < eps;
			
			bool flag = f1 && f2 && f3;

			Assert::IsTrue(flag);
		}

		//TEST_METHOD(EigenVectorsTest2)
		//{
		//	Math::mat3 m = Math::mat3(1, 0, 0,
		//		0, 1, 0,
		//		0, 0, 1);

		//	Math::vec3 vectors[3];
		//	Math::vec3 values(1, 1, 1);
		//	Math::EigenVectors(m, values, vectors);			

		//	Math::vec3 v1(1, 0, 0);
		//	Math::vec3 v2(0, 1, 0);
		//	Math::vec3 v3(0, 0, 1);			

		//	//	it is consodered that eigen vectors are the same if they have equal length and collinear
		//	//	but their direction may differ. I'm not quite sure is that ok !!!!!!

		//	float eps = 0.0001;
		//	bool f1 = Math::Abs(Math::Abs(v1.Dot(vectors[0])) - 1.0f) < eps;
		//	bool f2 = Math::Abs(Math::Abs(v2.Dot(vectors[1])) - 1.0f) < eps;
		//	bool f3 = Math::Abs(Math::Abs(v3.Dot(vectors[2])) - 1.0f) < eps;
		//	
		//	bool flag = f1 && f2 && f3;

		//	Assert::IsTrue(flag);
		//}

		TEST_METHOD(BBoxConstruction1)
		{
			std::vector<Math::vec3> points;
			points.push_back(Math::vec3(-1, -2, 1));
			points.push_back(Math::vec3(1, 0, 2));
			points.push_back(Math::vec3(2, -1, 3));
			points.push_back(Math::vec3(2, -1, 2));

			Math::BoundingBox bbox;
			bbox.Create(points[0], points.size(), sizeof(Math::vec3));
		}

	};
}