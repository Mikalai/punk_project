#ifndef ABSTRACT_SHADOW_MAP_DEBUG_VISUALIZER_H
#define ABSTRACT_SHADOW_MAP_DEBUG_VISUALIZER_H

namespace Gpu
{
    class Frame;

    class AbstractShadowMapDebugVisualizer
    {
    public:
        virtual void Draw(Frame* frame) = 0;
    };
}

#endif // ABSTRACT_SHADOW_MAP_DEBUG_VISUALIZER_H
