#include "geometry.h"

namespace Virtual
{
	Geometry::~Geometry()
	{
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

//	void Geometry::DropGPUCache()
//	{
//		delete m_cache.m_gpu_buffer;
//		m_cache.m_gpu_buffer = nullptr;
//	}

//	bool Geometry::IsGPUCacheValid()
//	{
//		return m_cache.m_gpu_buffer != nullptr;
//	}

//	void Geometry::SetGPUBufferCache(GPU::Renderable* value)
//	{
//		m_cache.m_gpu_buffer = value;
//	}

//	GPU::Renderable* Geometry::GetGPUBufferCache()
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
