#ifndef ABSTRACT_SHADOWMAP_RENDER_H
#define ABSTRACT_SHADOWMAP_RENDER_H

#include "../../../math/mat4.h"
#include "shadow_map_render_type.h"

namespace Gpu
{
    class VideoDriver;
    class Texture;
    class Frame;
    struct LightParameters;
    class AbstractShadowMapDebugVisualizer;

    class AbstractShadowMapRender
    {
    public:
        virtual Texture* GetShadowMap() = 0;
        virtual void Run(Frame* frame) = 0;
        virtual void SetLight(const LightParameters& value) = 0;
        virtual void SetViewProperties(float fov, float aspect, float n, float f, const Math::vec3& center, const Math::vec3& dir, const Math::vec3& up) = 0;
        virtual AbstractShadowMapDebugVisualizer* GetDebugVisualizer() = 0;
        virtual VideoDriver* GetVideoDriver() = 0;
    };

    PUNK_ENGINE_API AbstractShadowMapRender* CreateShadowMapRender(const ShadowMapRenderType& value, VideoDriver* driver);
}

#endif // ABSTRACT_SHADOWMAP_RENDER_H
