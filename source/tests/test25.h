/*
 *  Quaternion test
 *  Feature id:
 */


#ifndef TEST25_H
#define TEST25_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test25
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


#endif // TEST23_H
