#ifndef _H_PUNK_FRUSTUM_MESH
#define _H_PUNK_FRUSTUM_MESH

#include "../../../config.h"
#include "../../../math/frustum.h"
#include "../../../math/clip_space.h"
#include "../../../ai/interface.h"

namespace GPU
{
	class VideoDriver;
	class Renderable;

	GPU::Renderable* PUNK_ENGINE_API AsRenderable(const Math::Frustum& value, VideoDriver* driver);
    GPU::Renderable* PUNK_ENGINE_API AsRenderable(const Math::ClipSpace& value, VideoDriver* driver);
    GPU::Renderable* PUNK_ENGINE_API AsRenderable(const Math::Line3D* value, size_t count, float scale, VideoDriver* driver);
    GPU::Renderable* PUNK_ENGINE_API AsRenderable(const Math::vec3* value, size_t count, VideoDriver* driver);
	GPU::Renderable* PUNK_ENGINE_API AsRenderable(const Math::Plane* planes, size_t count, const Math::Frustum& frustum, VideoDriver* driver);
    GPU::Renderable* PUNK_ENGINE_API AsRenderable(const Math::BoundingBox& value, VideoDriver* driver);
    GPU::Renderable* PUNK_ENGINE_API AsRenderable(const Math::BoundingSphere& value, VideoDriver* driver);
    GPU::Renderable* PUNK_ENGINE_API AsRenderable(const AI::NaviMesh& value, VideoDriver* driver);
}

#endif	//	_H_PUNK_FRUSTUM_MESH
