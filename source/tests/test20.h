/*
  TIFF IMAGE LOADING
  */

#ifndef TEST20_H
#define TEST20_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test20
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
