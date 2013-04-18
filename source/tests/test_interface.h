#ifndef _H_PUNK_TEST_INTERFACE
#define _H_PUNK_TEST_INTERFACE

class TestInterface
{
public:

    /**
    *   Runs current test
    */
    virtual void Run() = 0;

    /**
    *   \return true if test passed, false otherwise
    */
    virtual bool Succeed() = 0;
};

#endif // _H_PUNK_TEST_INTERFACE
