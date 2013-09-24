#ifndef TERRAIN_MESH_H
#define TERRAIN_MESH_H

#include "../../system/object.h"
#include "../../system/aop/aop.h"

namespace Utility
{
    class AsyncParserTask;
}

namespace Virtual
{
    class StaticGeometry;
    class Material;

    class PUNK_ENGINE_API TerrainMesh : public System::Object
    {
    public:
        TerrainMesh();
        TerrainMesh(const TerrainMesh&) = delete;
        TerrainMesh& operator = (const TerrainMesh&) = delete;
        virtual ~TerrainMesh();

        void SetGeometry(StaticGeometry* geom);
        StaticGeometry* GetGeometry();
        const StaticGeometry* GetGeometry() const;

        void SetStaticMeshFilename(const System::string& filename);
        const System::string GetStaticMeshFilename() const;

        void SetName(const System::string& value);
        const System::string& GetName() const;

        Utility::AsyncParserTask* Task() const;
        Utility::AsyncParserTask* Task(Utility::AsyncParserTask* value);

    private:
        System::string m_name;
        System::string m_filename;
        StaticGeometry* m_geometry;
        Utility::AsyncParserTask* m_task;
        PUNK_OBJECT(TerrainMesh)
    };

    PUNK_OBJECT_UTIL(TerrainMesh)
}

#endif // TERRAIN_MESH_H
