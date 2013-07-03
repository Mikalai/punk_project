#ifndef _H_PUNK_VIRTUAL_STATIC_GEOMETRY
#define _H_PUNK_VIRTUAL_STATIC_GEOMETRY

#include <vector>
#include <map>

#include "../../math/bounding_box.h"
#include "../../system/aop/aop.h"
#include "geometry.h"

namespace GPU
{
    class VideoDriver;
}

namespace Virtual
{
    class PUNK_ENGINE_API StaticGeometry : public Geometry, public System::Aspect<StaticGeometry*, System::string>
    {
    public:
        typedef std::map<System::string, std::vector<Math::Vector4<Math::vec2>>> TextureMeshes;

        struct GpuCache
        {
            GpuCache(StaticGeometry& value);
            ~GpuCache();
            bool IsOnGpu();
            void Drop();
            void Update(GPU::VideoDriver* driver);
            GPU::Renderable* GetGpuBuffer();
            size_t GetGpuMemoryUsage() const;
        private:
            StaticGeometry& m_geom;
            GPU::Renderable* m_gpu_buffer;
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

            bool Save(std::ostream &stream) const;
            bool Load(std::istream &stream);

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

        virtual bool Save(std::ostream& stream) const;
        virtual bool Load(std::istream& stream);

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

    private:

        System::string m_filename;
        Math::mat4 m_world_offset;

        CpuCache m_cpu_cache;
        GpuCache m_gpu_cache;

        friend class CpuCache;
        friend class GpuCache;
    };
}

#endif
