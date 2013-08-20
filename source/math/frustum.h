#ifndef _H_PUNK_FRUSTUM
#define _H_PUNK_FRUSTUM

#include "../config.h"
#include "mat4.h"
#include "plane.h"
#include "aabb.h"
#include "clip_space.h"
#include "vec3.h"
#include "frustum_plane.h"
#include "frustum_points.h"

namespace Math
{
    struct FrustumCore
	{
        float neard;
        float fard;
        float fov;
        float ratio;
        vec3  point[8];
	};

        /**
      * Creates a clip space from current frustum and point.
      */
    PUNK_ENGINE_API const ClipSpace FrustumBuildClipSpaceFromPoint(const FrustumCore& f, const Math::vec3& p);
    PUNK_ENGINE_API const ClipSpace FrustumToClipSpace(const FrustumCore& f);
    PUNK_ENGINE_API const FrustumCore FrustumCreateFromProjectionMatrix(const Math::mat4& p);
    PUNK_ENGINE_API void ProjectionMatrixToPlanes(const Math::mat4& p, Math::Plane (&planes)[6]);
    PUNK_ENGINE_API void FrustumTransform(FrustumCore& f, const vec3 &center, const vec3 &view_dir, const vec3 &_up);
    PUNK_ENGINE_API const Math::mat4 FrustumCreatePerspectiveProjectionMatrix(const Math::FrustumCore& f);
}

#endif
