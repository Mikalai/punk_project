#ifndef _PUNK_PHYSICS_TERRAIN
#define _PUNK_PHYSICS_TERRAIN

#include "../config.h"

namespace Virtual { class TerrainView; }
namespace Physics
{
    class Simulator;

    class PUNK_ENGINE_API Terrain
    {
    public:
        virtual ~Terrain();
		void UpdateData(const Virtual::TerrainView* view);
		void EnterWorld(Simulator* world);
		void Leave();
		void Clear();
    };
}
#endif // _PUNK_PHYSICS_TERRAIN
