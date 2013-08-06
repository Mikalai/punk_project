/*
  SCENE GRAPH LOADING
  */

#ifndef TEST19_H
#define TEST19_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test19
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
