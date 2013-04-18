#include <iostream>
#include "test_create_opengl_window/test_create_opengl_window.h"


int main()
{
    std::cout << "Welcome to the test interface" << std::endl;
    CreateOpenGLWindow test1;
    test1.Run();

    std::cout << "Result " << (test1.Succeed()? "Pass" : "Failed") << std::endl;
    return 0;
}
