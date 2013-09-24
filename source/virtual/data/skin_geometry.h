#ifndef _H_PUNK_VIRTUAL_SKIN_GEOMETRY
#define _H_PUNK_VIRTUAL_SKIN_GEOMETRY

#include <vector>
#include <map>

#include <array>
#include "../../string/string.h"
#include "../../math/bounding_box.h"
#include "../../system/aop/aop.h"
#include "geometry.h"

namespace Gpu
{
    class VideoDriver;
}


namespace Virtual
{
    class Armature;
    class ArmatureAnimationMixer;

    class PUNK_ENGINE_API SkinGeometry : public Geometry
	{
	public:		
		typedef std::map<int, std::map<System::string, float>> BoneWeights;
        typedef std::map<System::string, std::vector<std::array<Math::vec2, 4>>> TextureMeshes;

	public:

        struct GpuCache
        {
            GpuCache(SkinGeometry& value);
            ~GpuCache();
            bool IsOnGpu();
            void Drop();
            void Update(Armature* armature, Gpu::VideoDriver* driver);
            Gpu::Renderable* GetGpuBuffer();
            size_t GetGpuMemoryUsage() const;
        private:
            SkinGeometry& m_geom;
            Gpu::Renderable* m_gpu_buffer;
        };

        struct CpuCache
        {
            CpuCache(SkinGeometry& value);
            bool IsOnCpu();
            void Drop();
            void Update();
            void Update(const System::string& path);
            size_t GetCpuMemoryUsage() const;

            void SetVertices(const Vertices& value);
            void SetNormals(const Normals& value);
            void SetFaces(const Faces& value);
            void SetTextureMeshes(const TextureMeshes& value);
            void SetBoneWeights(const BoneWeights& value);

            const Vertices& GetVertices() const;
            const Normals& GetNormals() const;
            const Faces& GetFaces() const;
            const TextureMeshes& GetTextureMeshes() const;
            const BoneWeights& GetBoneWeights() const;

            Vertices& GetVertices();
            Normals& GetNormals();
            Faces& GetFaces();
            TextureMeshes& GetTextureMeshes();
            BoneWeights& GetBoneWeights();

            void Save(System::Buffer *buffer) const;
            void Load(System::Buffer *buffer);
        private:
            SkinGeometry& m_geom;
            Vertices m_vertices;
            Normals m_normals;
            Faces m_faces;
            TextureMeshes m_tex_coords;
            BoneWeights m_bone_weights;
            bool m_is_on_cpu;
        };


    public:
		SkinGeometry();
        SkinGeometry(const SkinGeometry&) = delete;
        SkinGeometry& operator = (const SkinGeometry&) = delete;
        virtual ~SkinGeometry();

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
        void SetBoneWeights(const BoneWeights& value);

        const Vertices& GetVertices() const;
        const Normals& GetNormals() const;
        const Faces& GetFaces() const;
        const TextureMeshes& GetTextureMeshes() const;
        const BoneWeights& GetBoneWeights() const;

        void SetWorldOffset(const Math::mat4& value);
        const Math::mat4& GetWorldOffset() const;

        void SetFilename(const System::string& filename);
        const System::string& GetFilename() const;

        GpuCache& GetGpuCache();
        CpuCache& GetCpuCache();

        void SetArmatureName(const System::string& name);
        const System::string& GetArmatureName() const;

        void SetName(const System::string& value);
        const System::string& GetName() const;

    private:

        System::string m_armature_name;
        System::string m_filename;
        System::string m_name;

        Math::mat4 m_world_offset;

        CpuCache m_cpu_cache;
        GpuCache m_gpu_cache;

        friend class CpuCache;
        friend class GpuCache;

        PUNK_OBJECT(SkinGeometry)        
	};

    PUNK_OBJECT_UTIL(SkinGeometry)
}

#endif	//	_H_PUNK_VIRTUAL_SKIN_GEOMETRY
