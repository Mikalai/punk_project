#include <memory>
#include "../../utility/descriptors/light_desc.h"
#include "light.h"
#include "lights/point_light.h"
#include "../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(Light, "Virtual.Light", PUNK_POINT_LIGHT, &System::Object::Info.Type);

    Light::Light()
    {
        Info.Add(this);
    }

    Light::~Light()
    {
        Info.Remove(this);
    }
}
