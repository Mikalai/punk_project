/*
  RIVER TEST
  */

#ifndef TEST18_H
#define TEST18_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test18
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
