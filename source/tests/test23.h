/*
 *  Solid color + per vertex light + specular + no shadows
 *  Feature id: 23
 */


#ifndef TEST23_H
#define TEST23_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test23
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
