/*
SKINNING TEST
  */

#ifndef TEST21_H
#define TEST21_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test21
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
