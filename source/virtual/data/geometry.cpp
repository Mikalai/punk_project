#include "geometry.h"
#include "../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(Geometry, "Virtual.Geometry", PUNK_GEOMETRY, SaveGeometry, LoadGeometry, &System::Object::Info.Type);

    Geometry::Geometry()
    {
        Info.Add(this);
    }

	Geometry::~Geometry()
	{
        Info.Remove(this);
//		safe_delete(m_cache.m_gpu_buffer);
//		safe_delete(m_cache.m_physics_buffer);
	}

    Math::BoundingBox& Geometry::GetBoundingBox()
    {
        return m_bbox;
    }

    const Math::BoundingBox& Geometry::GetBoundingBox() const
    {
        return m_bbox;
    }

    Math::BoundingSphere& Geometry::GetBoundingSphere()
    {
        return m_sphere;
    }

    const Math::BoundingSphere& Geometry::GetBoundingSphere() const
    {
        return m_sphere;
    }

    void SaveGeometry(System::Buffer* buffer, const System::Object* o)
    {
        System::SaveObject(buffer, o);
    }

    void LoadGeometry(System::Buffer* buffer, System::Object* o)
    {
        System::LoadObject(buffer, o);
    }

//	void Geometry::DropGPUCache()
//	{
//		delete m_cache.m_gpu_buffer;
//		m_cache.m_gpu_buffer = nullptr;
//	}

//	bool Geometry::IsGPUCacheValid()
//	{
//		return m_cache.m_gpu_buffer != nullptr;
//	}

//	void Geometry::SetGPUBufferCache(Gpu::Renderable* value)
//	{
//		m_cache.m_gpu_buffer = value;
//	}

//	Gpu::Renderable* Geometry::GetGPUBufferCache()
//	{
//		return m_cache.m_gpu_buffer;
//	}

//	void Geometry::DropPhysicsCache()
//	{
//		delete m_cache.m_physics_buffer;
//	}

//	bool Geometry::IsPhysicsCacheValid()
//	{
//		return m_cache.m_physics_buffer != nullptr;
//	}

//	void Geometry::SetPhysicsCache(System::Object* value)
//	{
//		m_cache.m_physics_buffer = value;
//	}

//	System::Object* Geometry::GetPhysicsCache()
//	{
//		return m_cache.m_physics_buffer;
//	}
}
