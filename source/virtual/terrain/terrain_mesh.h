#ifndef TERRAIN_MESH_H
#define TERRAIN_MESH_H

#include "../../system/object.h"
#include "../../system/aop/aop.h"

namespace Virtual
{
    class StaticGeometry;
    class Material;

    class PUNK_ENGINE_API TerrainMesh : public System::Object, public System::Aspect<TerrainMesh*, System::string>
    {
    public:
        TerrainMesh();
        virtual ~TerrainMesh();

        void SetGeometry(StaticGeometry* geom);
        StaticGeometry* GetGeometry();
        const StaticGeometry* GetGeometry() const;

        void SetStaticMeshFilename(const System::string& filename);
        const System::string GetStaticMeshFilename() const;
    private:
        System::string m_filename;
        StaticGeometry* m_geometry;
    };
}

#endif // TERRAIN_MESH_H
