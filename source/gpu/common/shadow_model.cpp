#include "shadow_model.h"

namespace Gpu
{
    using ShadowModelDesc = std::pair<ShadowModel, System::string>;
    static const ShadowModelDesc g_shadow_models[] = {
        ShadowModelDesc(ShadowModel::ShadowMapSingle, L"ShadowMap")
    };

    const System::string AsString(ShadowModel value)
    {
        for (size_t i = 0; i != std::extent<decltype(g_shadow_models)>::value; ++i)
        {
            if (g_shadow_models[i].first == value)
                return g_shadow_models[i].second;
        }
        return L"ERROR";
    }


}
