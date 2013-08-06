#ifndef _H_CREATE_OPENGL_WINDOW_TEST
#define _H_CREATE_OPENGL_WINDOW_TEST

#include "../../punk_engine.h"
#include "../test_interface.h"

namespace Test1
{
class Test : public TestInterface
{
public:

    /**
    *   Runs current test
    */
    void Run() override;

    /**
    *   \return true if test passed, false otherwise
    */
    bool Succeed() override;

private:
    bool m_result;
};
}

#endif // _H_CREATE_OPENGL_WINDOW_TEST
