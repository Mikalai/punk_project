#ifdef USE_BULLET_PHYSICS
#define HAS_PHYSICS
#include "bullet/module.h"
#else
#include "physical_simulator.h"
#include "../system/errors/module.h"
#endif // USE_PHYSIX

namespace Physics
{
    void Simulator::Update(float dt)
    {
        #ifdef HAS_PHYSICS
        #else
        (void)dt;
        throw System::PunkException(L"Physics simulator is not available");
        #endif // HAS_PHYSICS
    }

    void Simulator::Init()
    {
        #ifdef HAS_PHYSICS
        #else
        throw System::PunkException(L"Physics simulator is not available");
        #endif // HAS_PHYSICS
    }
}
