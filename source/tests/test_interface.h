#ifndef _H_PUNK_TEST_INTERFACE
#define _H_PUNK_TEST_INTERFACE

class TestInterface
{
public:

    /**
    *   Runs current test
    */
    virtual void Run() override;

    /**
    *   \return true if test passed, false otherwise
    */
    virtual bool Succeed() override;
};

#endif // _H_PUNK_TEST_INTERFACE
