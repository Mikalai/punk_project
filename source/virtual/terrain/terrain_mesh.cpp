#include "terrain_mesh.h"

namespace Virtual
{
    TerrainMesh::TerrainMesh()
    {
    }

    TerrainMesh::~TerrainMesh()
    {
        delete m_geometry;
    }
}
