#ifndef _H_PUNK_VIRTUAL_STATIC_GEOMETRY
#define _H_PUNK_VIRTUAL_STATIC_GEOMETRY

#include <array>
#include <vector>
#include <map>

#include "../../math/bounding_box.h"
#include "../../math/vec2.h"
#include "../../system/aop/aop.h"
#include "geometry.h"

namespace Gpu
{
    class VideoDriver;
}

namespace Virtual
{
    class PUNK_ENGINE_API StaticGeometry : public Geometry
    {
    public:
        typedef std::map<System::string, std::vector<std::array<Math::vec2, 4>>> TextureMeshes;

        struct GpuCache
        {
            GpuCache(StaticGeometry& value);
            ~GpuCache();
            bool IsOnGpu();
            void Drop();
            void Update(Gpu::VideoDriver* driver);
            Gpu::Renderable* GetGpuBuffer();
            size_t GetGpuMemoryUsage() const;
        private:
            StaticGeometry& m_geom;
            Gpu::Renderable* m_gpu_buffer;
        };

        struct CpuCache
        {
            CpuCache(StaticGeometry& value);
            bool IsOnCpu();
            void Drop();
            void Update();
            void Update(const System::string& path);
            size_t GetCpuMemoryUsage() const;

            void SetVertices(const Vertices& value);
            void SetNormals(const Normals& value);
            void SetFaces(const Faces& value);
            void SetTextureMeshes(const TextureMeshes& value);

            const Vertices& GetVertices() const;
            const Normals& GetNormals() const;
            const Faces& GetFaces() const;
            const TextureMeshes& GetTextureMeshes() const;

            Vertices& GetVertices();
            Normals& GetNormals();
            Faces& GetFaces();
            TextureMeshes& GetTextureMeshes();

//            bool Save(std::ostream &stream) const;
//            bool Load(std::istream &stream);

        private:
            StaticGeometry& m_geom;
            Vertices m_vertices;
            Normals m_normals;
            Faces m_faces;
            TextureMeshes m_tex_coords;
            bool m_is_on_cpu;
        };

    public:

        StaticGeometry();
        virtual ~StaticGeometry();

//        virtual void Save(System::Buffer* buffer) const;
//        virtual void Load(System::Buffer* buffer);

        virtual Vertices& GetVertexArray() override;
        virtual Normals& GetNormalArray() override;
        virtual Faces& GetFaceArray() override;
        virtual const Vertices& GetVertexArray() const override;
        virtual const Normals& GetNormalArray() const override;
        virtual const Faces& GetFaceArray() const override;

        void SetVertices(const Vertices& value);
        void SetNormals(const Normals& value);
        void SetFaces(const Faces& value);
        void SetTextureMeshes(const TextureMeshes& value);

        const Vertices& GetVertices() const;
        const Normals& GetNormals() const;
        const Faces& GetFaces() const;
        const TextureMeshes& GetTextureMeshes();

        void SetWorldOffset(const Math::mat4& value);
        const Math::mat4& GetWorldOffset() const;

        void SetFilename(const System::string& filename);
        const System::string& GetFilename() const;

        GpuCache& GetGpuCache();
        CpuCache& GetCpuCache();

        void SetName(const System::string& value);
        const System::string& GetName() const;

    private:

        System::string m_name;
        System::string m_filename;
        Math::mat4 m_world_offset;

        CpuCache m_cpu_cache;
        GpuCache m_gpu_cache;

        friend class CpuCache;
        friend class GpuCache;

        PUNK_OBJECT(StaticGeometry)
    };

    PUNK_OBJECT_UTIL(StaticGeometry)
}

#endif
