#ifndef TERRAIN_MESH_H
#define TERRAIN_MESH_H

#include "../../system/object.h"

namespace Virtual
{
    class StaticGeometry;
    class Material;

    class PUNK_ENGINE_API TerrainMesh : public System::Object
    {
    public:
        TerrainMesh();
        virtual ~TerrainMesh();
    private:
        StaticGeometry* m_geometry;
    };
}

#endif // TERRAIN_MESH_H
