#ifndef SHADOW_MODEL_H
#define SHADOW_MODEL_H

#include "config.h"
#include "../../string/string.h"

namespace Gpu
{
    enum class ShadowModel { ShadowMapSimple, ShadowMapCascade };

    extern PUNK_ENGINE_API const System::string AsString(ShadowModel value);
}

#endif // SHADOW_MODEL_H
