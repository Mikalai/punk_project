#ifndef _H_TEST0
#define _H_TEST0

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test0
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

#endif // _H_TEST0
