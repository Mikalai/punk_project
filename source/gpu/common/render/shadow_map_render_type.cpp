#include "shadow_map_render_type.h"

namespace Gpu
{
    const System::string AsString(const ShadowMapRenderType& value)
    {
        switch(value)
        {
        case ShadowMapRenderType::SimpleRender:
            return L"SimpleShadowMapRender";
        case ShadowMapRenderType::CascadeRender:
            return L"CascadeShadowMapRender";
        case ShadowMapRenderType::BadRender:
        default:
            return L"BadShadowRender";
        }
    }
}
