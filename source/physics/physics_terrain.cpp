#if USE_BULLET_PHYSICS
#define HAS_PHYSICS
#include "bullet/module.h"
#else
#include "physics_terrain.h"
#include "../system/errors/module.h"
#endif // USE_PHYSIX

namespace Physics
{
    void Terrain::UpdateData(const Virtual::TerrainView* view)
    {
        #ifdef HAS_PHYSICS
        #else
        (void)view;
        throw System::PunkException(L"Physics simulator is not available");
        #endif // HAS_PHYSICS
    }

    void Terrain::EnterWorld(Simulator* simulator)
    {
        #ifdef HAS_PHYSICS
        #else
        (void)simulator;
        throw System::PunkException(L"Physics simulator is not available");
        #endif // HAS_PHYSICS
    }

    Terrain::~Terrain()
    {
    }
}
