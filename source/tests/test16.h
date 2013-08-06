#ifndef TEST16_H
#define TEST16_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test16
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
