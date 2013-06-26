#include "terrain_mesh.h"
#include "../data/static_geometry.h"

namespace Virtual
{
    TerrainMesh::TerrainMesh()
        : m_geometry(nullptr)
    {
    }

    TerrainMesh::~TerrainMesh()
    {
    }

    void TerrainMesh::SetGeometry(StaticGeometry* geom)
    {
        m_geometry = geom;
    }

    StaticGeometry* TerrainMesh::GetGeometry()
    {
        return m_geometry;
    }

    const StaticGeometry* TerrainMesh::GetGeometry() const
    {
        return m_geometry;
    }

    void TerrainMesh::SetStaticMeshFilename(const System::string& filename)
    {
        m_filename = filename;
    }

    const System::string TerrainMesh::GetStaticMeshFilename() const
    {
        return m_filename;
    }
}
