#include "terrain_mesh.h"
#include "../data/static_geometry.h"
#include "../../engine_objects.h"
#include "../../utility/module.h"

namespace Virtual
{
    PUNK_OBJECT_REG(TerrainMesh, "Virtual.TerrainMesh", PUNK_TERRAIN_MESH, &System::Object::Info.Type);

    TerrainMesh::TerrainMesh()
        : m_geometry(nullptr)
        , m_task(nullptr)
    {
        Info.Add(this);
    }

    TerrainMesh::~TerrainMesh()
    {
        delete m_task;
        Info.Remove(this);
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

    void TerrainMesh::SetName(const System::string& value)
    {
        m_name = value;
    }

    const System::string& TerrainMesh::GetName() const
    {
        return m_name;
    }

    Utility::AsyncParserTask* TerrainMesh::Task() const
    {
        return m_task;
    }

    Utility::AsyncParserTask* TerrainMesh::Task(Utility::AsyncParserTask* value)
    {
        if (m_task)
            delete m_task;
        return m_task = value;
    }

}
