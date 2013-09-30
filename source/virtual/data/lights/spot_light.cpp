#include "../../../engine_objects.h"
#include "../../../system/buffer.h"
#include "../../../math/vec2.h"
#include "../../../math/vec3.h"
#include "../../../math/vec4.h"
#include "spot_light.h"

namespace Virtual
{
    PUNK_OBJECT_REG(SpotLight, "Virtual.SpotLight", PUNK_SPOT_LIGHT, SaveSpotLight, LoadSpotLight, &Light::Info.Type);

    SpotLight::SpotLight()
    {
        Info.Add(this);
    }

    SpotLight::~SpotLight()
    {
        Info.Remove(this);
    }

    void SaveSpotLight(System::Buffer *buffer, const System::Object *o)
    {
        SaveLight(buffer, o);
    }

    void LoadSpotLight(System::Buffer *buffer, System::Object *o)
    {
        LoadLight(buffer, o);
    }
}
