/*
    Solid color
*/

#ifndef TEST22_H
#define TEST22_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test22
{
    class Test : public TestInterface
    {
    public:
        void Run();
        bool Succeed();

    private:
        bool m_result;
    };
}

#endif // TEST10_H
