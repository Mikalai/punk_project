/*
 *  Transform node loading
 *  Feature id: 161
 */


#ifndef TEST24_H
#define TEST24_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test24
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
