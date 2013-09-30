/*
 *  Test of loading a simple scene from text file with some objects
 *  and a light source.
 *  Feature id:
 */


#ifndef TEST26_H
#define TEST26_H

#include "../punk_engine.h"
#include "test_interface.h"

namespace Test26
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
