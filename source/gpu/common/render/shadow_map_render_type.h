#ifndef SHADOW_MAP_RENDER_TYPE_H
#define SHADOW_MAP_RENDER_TYPE_H

#include "../../../string/string.h"

namespace Gpu
{
    enum class ShadowMapRenderType { BadRender, SimpleRender, CascadeRender };

    const System::string AsString(const ShadowMapRenderType& value);
}

#endif // SHADOW_MAP_RENDER_TYPE_H
