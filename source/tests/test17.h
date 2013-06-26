#ifndef TEST17_H
#define TEST17_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test17
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
