#ifndef _H_PUNK_FRUSTUM_MESH
#define _H_PUNK_FRUSTUM_MESH

#include "../../../config.h"
#include "../../../math/frustum.h"
#include "../../../math/clip_space.h"
#include "../../../ai/interface.h"

namespace Gpu
{
	class VideoDriver;
	class Renderable;

    PUNK_ENGINE_API Gpu::Renderable* AsRenderable(const Math::Frustum& value, VideoDriver* driver);
    PUNK_ENGINE_API Gpu::Renderable* AsRenderable(const Math::ClipSpace& value, VideoDriver* driver);
    PUNK_ENGINE_API Gpu::Renderable* AsRenderable(const Math::Line3D* value, size_t count, float scale, VideoDriver* driver);
    PUNK_ENGINE_API Gpu::Renderable* AsRenderable(const Math::vec3* value, size_t count, VideoDriver* driver);
    PUNK_ENGINE_API Gpu::Renderable* AsRenderable(const Math::Plane* planes, size_t count, const Math::Frustum& frustum, VideoDriver* driver);
    PUNK_ENGINE_API Gpu::Renderable* AsRenderable(const Math::BoundingBox& value, VideoDriver* driver);
    PUNK_ENGINE_API Gpu::Renderable* AsRenderable(const Math::BoundingSphere& value, VideoDriver* driver);
    PUNK_ENGINE_API Gpu::Renderable* AsRenderable(const AI::NaviMesh& value, VideoDriver* driver);
    PUNK_ENGINE_API Gpu::Renderable* AsRenderable(const Math::vec3& p0, const Math::vec3& p1, VideoDriver* driver);
}

#endif	//	_H_PUNK_FRUSTUM_MESH
