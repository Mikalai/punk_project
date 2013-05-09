#ifndef FIRSTTRIANGLEANDQUAD_H
#define FIRSTTRIANGLEANDQUAD_H

#include "../../punk_engine.h"
#include "../test_interface.h"

class TestTriangleQuad : public TestInterface
{
public:
    /**
    *   Runs current test
    */
    void Run() override;

    /**
    *   \return true if test passed, false otherwise
    */
    bool Succeed() override;

private:
    bool m_result;
};

#endif // FIRSTTRIANGLEANDQUAD_H
