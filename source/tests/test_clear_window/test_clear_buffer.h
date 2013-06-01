#ifndef TEST_CLEAR_BUFFER_H
#define TEST_CLEAR_BUFFER_H

#include "../../punk_engine.h"
#include "../test_interface.h"

class TestClearBuffer : public TestInterface
{
public:
    TestClearBuffer();

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

#endif // TEST_CLEAR_BUFFER_H
