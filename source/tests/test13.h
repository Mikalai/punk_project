#ifndef TEST13_H
#define TEST13_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test13
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
