#include <fstream>
#include <memory>
#include "../../gpu/common/module.h"
#include "static_geometry.h"
#include "../../utility/parser/parser.h"
#include "../../system/environment.h"
#include "../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(StaticGeometry,"Virtual.StaticGeometry", PUNK_STATIC_GEOMETRY, &Geometry::Info.Type);

    StaticGeometry::GpuCache::GpuCache(StaticGeometry& value)
        : m_geom(value)
        , m_gpu_buffer(nullptr)
    {}

    StaticGeometry::GpuCache::~GpuCache()
    {
        Drop();
    }

    bool StaticGeometry::GpuCache::IsOnGpu()
    {
        return m_gpu_buffer != nullptr;
    }

    size_t StaticGeometry::GpuCache::GetGpuMemoryUsage() const
    {
        return m_gpu_buffer->GetMemoryUsage();
    }

    void StaticGeometry::GpuCache::Drop()
    {
        delete m_gpu_buffer;
        m_gpu_buffer = nullptr;
    }

    void StaticGeometry::GpuCache::Update(Gpu::VideoDriver* driver)
    {
        if (!m_geom.GetCpuCache().IsOnCpu())
            m_geom.GetCpuCache().Update();

        Drop();
        Gpu::StaticMesh* mesh = new Gpu::StaticMesh(driver);
        mesh->Cook(&m_geom);
        m_gpu_buffer = mesh;
    }

    Gpu::Renderable* StaticGeometry::GpuCache::GetGpuBuffer()
    {
        return m_gpu_buffer;
    }

    StaticGeometry::CpuCache::CpuCache(StaticGeometry &value)
        : m_geom(value)
        , m_is_on_cpu(false)
    {}


    void StaticGeometry::CpuCache::SetVertices(const Vertices& value)
    {
        m_vertices = value;
        m_is_on_cpu = true;
        m_geom.m_bbox.Create(m_vertices);
        m_geom.m_sphere.Create(m_vertices);
    }

    void StaticGeometry::CpuCache::SetNormals(const Normals& value)
    {
        m_normals = value;
    }

    void StaticGeometry::CpuCache::SetFaces(const Faces& value)
    {
        m_faces = value;
    }

    void StaticGeometry::CpuCache::SetTextureMeshes(const TextureMeshes& value)
    {
        m_tex_coords = value;
    }

    const StaticGeometry::Vertices& StaticGeometry::CpuCache::GetVertices() const
    {
        return m_vertices;
    }

    const StaticGeometry::Normals& StaticGeometry::CpuCache::GetNormals() const
    {
        return m_normals;
    }

    const StaticGeometry::Faces& StaticGeometry::CpuCache::GetFaces() const
    {
        return m_faces;
    }

    const StaticGeometry::TextureMeshes& StaticGeometry::CpuCache::GetTextureMeshes() const
    {
        return m_tex_coords;
    }

    StaticGeometry::Vertices& StaticGeometry::CpuCache::GetVertices()
    {
        return m_vertices;
    }

    StaticGeometry::Normals& StaticGeometry::CpuCache::GetNormals()
    {
        return m_normals;
    }

    StaticGeometry::Faces& StaticGeometry::CpuCache::GetFaces()
    {
        return m_faces;
    }

    StaticGeometry::TextureMeshes& StaticGeometry::CpuCache::GetTextureMeshes()
    {
        return m_tex_coords;
    }

    bool StaticGeometry::CpuCache::IsOnCpu()
    {
        return m_is_on_cpu;
    }

    void StaticGeometry::CpuCache::Drop()
    {
        m_is_on_cpu = false;
        Vertices v;
        m_vertices.swap(v);
        Normals n;
        m_normals.swap(n);
        Faces f;
        m_faces.swap(f);
        TextureMeshes t;
        m_tex_coords.swap(t);
    }

    void StaticGeometry::CpuCache::Update(const System::string &path)
    {
        Drop();
        StaticGeometry* geom = dynamic_cast<StaticGeometry*>(Utility::ParsePunkFile(path));
        if (!geom)
            return;
        m_geom.SetVertices(geom->GetVertices());
        m_geom.SetNormals(geom->GetNormals());
        m_geom.SetFaces(geom->GetFaces());
        m_geom.SetTextureMeshes(geom->GetTextureMeshes());
        m_geom.SetWorldOffset(geom->GetWorldOffset());
        m_is_on_cpu = true;
        delete geom;
    }

    void StaticGeometry::CpuCache::Update()
    {
        Drop();
        StaticGeometry* geom = dynamic_cast<StaticGeometry*>(Utility::ParsePunkFile(System::Environment::Instance()->GetModelFolder() + m_geom.GetFilename()));
        if (!geom)
            return;
        m_geom.SetVertices(geom->GetVertices());
        m_geom.SetNormals(geom->GetNormals());
        m_geom.SetFaces(geom->GetFaces());
        m_geom.SetTextureMeshes(geom->GetTextureMeshes());
        m_geom.SetWorldOffset(geom->GetWorldOffset());
        m_is_on_cpu = true;
        delete geom;
    }

    size_t StaticGeometry::CpuCache::GetCpuMemoryUsage() const
    {
        size_t res = 0;
        res += m_vertices.size() * sizeof(m_vertices[0]);
        res += m_normals.size() * sizeof(m_normals[0]);
        res += m_faces.size() * sizeof(m_faces[0]);
        for (auto i : m_tex_coords)
        {
            res += i.second.size() * sizeof(i.second[0]);
        }
        return res;
    }

//    bool StaticGeometry::CpuCache::Save(std::ostream &stream) const
//    {
//        if (m_vertices.empty() || m_normals.empty() || m_faces.empty() || m_tex_coords.empty())
//            throw System::PunkInvalidArgumentException(L"Can't save static geometry");

//        int size = (int)m_vertices.size();
//        stream.write((char*)&size, sizeof(size));
//        stream.write((char*)&m_vertices[0], sizeof(m_vertices[0])*size);
//        size = (int)m_faces.size();
//        stream.write((char*)&size, sizeof(size));
//        stream.write((char*)&m_faces[0], sizeof(m_faces[0])*size);
//        size = (int)m_normals.size();
//        stream.write((char*)&size, sizeof(size));
//        stream.write((char*)&m_normals[0], sizeof(m_normals[0])*size);
//        int count = (int)m_tex_coords.size();
//        stream.write((char*)&count, sizeof(count));
//        for (auto it = m_tex_coords.begin(); it != m_tex_coords.end(); ++it)
//        {
//            it->first.Save(stream);
//            size = (int)it->second.size();
//            stream.write((char*)&size, sizeof(size));
//            stream.write((char*)&it->second[0], sizeof(it->second[0]) * size);
//        }
//        return true;
//    }

//    bool StaticGeometry::CpuCache::Load(std::istream &stream)
//    {
//        int size override;
//        stream.read((char*)&size, sizeof(size));
//        m_vertices.resize(size);
//        stream.read((char*)&m_vertices[0], sizeof(m_vertices[0])*size);

//        size override;
//        stream.read((char*)&size, sizeof(size));
//        m_faces.resize(size);
//        stream.read((char*)&m_faces[0], sizeof(m_faces[0])*size);

//        size override;
//        stream.read((char*)&size, sizeof(size));
//        m_normals.resize(size);
//        stream.read((char*)&m_normals[0], sizeof(m_normals[0])*size);

//        int count= 0;
//        stream.read((char*)&count, sizeof(count));
//        for (int i = 0; i < count; ++i)
//        {
//            System::string name;
//            name.Load(stream);
//            size override;
//            stream.read((char*)&size, sizeof(size));
//            std::vector<Math::Vector4<Math::vec2>> v;
//            v.resize(size);
//            stream.read((char*)&v[0], sizeof(v[0]) * size);
//            m_tex_coords[name] = v;
//        }
//        m_is_on_cpu = true;
//        return true;
//    }

    StaticGeometry::StaticGeometry()
        : m_cpu_cache(*this)
        , m_gpu_cache(*this)
    {
        Info.Add(this);
    }

    StaticGeometry::~StaticGeometry()
    {
        Info.Remove(this);
    }

//    bool StaticGeometry::Save(std::ostream& stream) const
//    {
//        Geometry::Save(stream);
//        m_bbox.Save(stream);
//        return m_cpu_cache.Save(stream);
//    }

//    bool StaticGeometry::Load(std::istream& stream)
//    {
//        Geometry::Load(stream);
//        m_bbox.Load(stream);
//        return m_cpu_cache.Load(stream);
//    }

    StaticGeometry::Vertices& StaticGeometry::GetVertexArray()
    {
        return m_cpu_cache.GetVertices();
    }

    StaticGeometry::Normals& StaticGeometry::GetNormalArray()
    {
        return m_cpu_cache.GetNormals();
    }

    StaticGeometry::Faces& StaticGeometry::GetFaceArray()
    {
        return m_cpu_cache.GetFaces();
    }

    const StaticGeometry::Vertices& StaticGeometry::GetVertexArray() const
    {
        return m_cpu_cache.GetVertices();
    }

    const StaticGeometry::Normals& StaticGeometry::GetNormalArray() const
    {
        return m_cpu_cache.GetNormals();
    }

    const StaticGeometry::Faces& StaticGeometry::GetFaceArray() const
    {
        return m_cpu_cache.GetFaces();
    }

    void StaticGeometry::SetVertices(const StaticGeometry::Vertices& value)
    {
        m_cpu_cache.SetVertices(value);
    }

    void StaticGeometry::SetNormals(const Normals& value)
    {
        m_cpu_cache.SetNormals(value);
    }

    void StaticGeometry::SetFaces(const StaticGeometry::Faces& value)
    {
        m_cpu_cache.SetFaces(value);
    }

    void StaticGeometry::SetTextureMeshes(const StaticGeometry::TextureMeshes& value)
    {
        m_cpu_cache.SetTextureMeshes(value);
    }

    const StaticGeometry::Vertices& StaticGeometry::GetVertices() const
    {
        return m_cpu_cache.GetVertices();
    }

    const StaticGeometry::Normals& StaticGeometry::GetNormals() const
    {
        return m_cpu_cache.GetNormals();
    }

    const StaticGeometry::Faces& StaticGeometry::GetFaces() const
    {
        return m_cpu_cache.GetFaces();
    }

    const StaticGeometry::TextureMeshes& StaticGeometry::GetTextureMeshes()
    {
        return m_cpu_cache.GetTextureMeshes();
    }

    void StaticGeometry::SetWorldOffset(const Math::mat4& value)
    {
        m_world_offset = value;
    }

    const Math::mat4& StaticGeometry::GetWorldOffset() const
    {
        return m_world_offset;
    }

    void StaticGeometry::SetFilename(const System::string& filename)
    {
        m_filename = filename;
    }

    const System::string& StaticGeometry::GetFilename() const
    {
        return m_filename;
    }

    StaticGeometry::GpuCache& StaticGeometry::GetGpuCache()
    {
        return m_gpu_cache;
    }

    StaticGeometry::CpuCache& StaticGeometry::GetCpuCache()
    {
        return m_cpu_cache;
    }

    void StaticGeometry::SetName(const System::string& value)
    {
        m_name = value;
    }

    const System::string& StaticGeometry::GetName() const
    {
        return m_name;
    }
}
