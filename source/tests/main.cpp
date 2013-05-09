#include <iostream>
#include "test_create_opengl_window/test_create_opengl_window.h"
#include "test_clear_window/test_clear_buffer.h"
#include "test_first_triangle/firsttriangleandquad.h"
#include "colored_triangle_test.h"
#include "rotate_triangle.h"
#include "test5.h"
#include "test6.h"
#include "test7.h"
#include "test8.h"

static const int TestNumber = 9;

int main()
{
	std::cout << "Welcome to the test interface" << std::endl;
	if (TestNumber == 1)
	{
		CreateOpenGLWindow test1;
		test1.Run();
		std::cout << "Result " << (test1.Succeed()? "Pass" : "Failed") << std::endl;
	}
	else if (TestNumber == 2)
	{
		TestClearBuffer test2;
		test2.Run();
		std::cout << "Result " << (test2.Succeed()? "Pass" : "Failed") << std::endl;
	}
	else if (TestNumber == 3)
	{
		TestTriangleQuad test3;
		test3.Run();
		std::cout << "Result " << (test3.Succeed()? "Pass" : "Failed") << std::endl;
	}
	else if (TestNumber == 4)
	{
		Test3::Test test;
		test.Run();
		std::cout << "Result " << (test.Succeed()? "Pass" : "Failed") << std::endl;
	}
	else if (TestNumber == 5)
	{
		Test4::Test test;
		test.Run();
		std::cout << "Result " << (test.Succeed()? "Pass" : "Failed") << std::endl;
	}
	else if (TestNumber == 6)
	{
		Test5::Test test;
		test.Run();
		std::cout << "Result " << (test.Succeed()? "Pass" : "Failed") << std::endl;
	}
	else if (TestNumber == 7)
	{
		Test6::Test test;
		test.Run();
		std::cout << "Result " << (test.Succeed()? "Pass" : "Failed") << std::endl;
	}
	else if (TestNumber == 8)
	{
		Test7::Test test;
		test.Run();
		std::cout << "Result " << (test.Succeed()? "Pass" : "Failed") << std::endl;
	}
	else if (TestNumber == 9)
	{
		Test8::Test test;
		test.Run();
		std::cout << "Result " << (test.Succeed()? "Pass" : "Failed") << std::endl;
	}
	return 0;
}
