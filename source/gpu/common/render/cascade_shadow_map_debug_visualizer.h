#ifndef CASCADE_SHADOW_MAP_DEBUG_VISUALIZER_H
#define CASCADE_SHADOW_MAP_DEBUG_VISUALIZER_H

#include "abstract_shadow_map_debug_visualizer.h"

namespace Gpu
{
    class CascadeShadowMapRender;

    class CascadeShadowMapDebugVisualizer : public AbstractShadowMapDebugVisualizer
    {
    public:
        CascadeShadowMapDebugVisualizer(CascadeShadowMapRender* render);
        virtual void Draw(Frame *frame) override;
    private:
        CascadeShadowMapRender* m_shadow_map_render;
    };
}

#endif // CASCADE_SHADOW_MAP_DEBUG_VISUALIZER_H
