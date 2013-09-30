#include "test0.h"

namespace Test0
{

    void Test::Run()
    {
        m_result = true;
        try
        {
            System::Window wnd(nullptr);
            wnd.SetTitle("Test0");
            wnd.Loop();
            std::cout << "Window has been closed" << std::endl;
        }
        catch(...)
        {            
           m_result = false;
        }
        std::cout << "Test finished" << std::endl;
    }

    bool Test::Succeed()
    {
        return m_result;
    }
}
