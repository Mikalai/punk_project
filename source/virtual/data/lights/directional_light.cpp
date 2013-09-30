#include "../../../engine_objects.h"
#include "../../../system/buffer.h"
#include "../../../math/vec2.h"
#include "../../../math/vec3.h"
#include "../../../math/vec4.h"
#include "directional_light.h"

namespace Virtual
{
    PUNK_OBJECT_REG(DirectionalLight, "Virtual.DirectionalLight", PUNK_DIR_LIGHT, SaveDirectionalLight, LoadDirectionalLight, &Light::Info.Type);

    DirectionalLight::DirectionalLight()
    {
        Info.Add(this);
    }

    DirectionalLight::~DirectionalLight()
    {
        Info.Remove(this);
    }

    void SaveDirectionalLight(System::Buffer *buffer, const System::Object *o)
    {
        SaveLight(buffer, o);
        const DirectionalLight* l = Cast<const DirectionalLight*>(o);
        Math::SaveVector3f(buffer, l->m_direction);
        Math::SaveVector3f(buffer, l->m_color);
        buffer->WriteReal32(l->m_distance);
        buffer->WriteReal32(l->m_energy);
    }

    void LoadDirectionalLight(System::Buffer *buffer, System::Object *o)
    {
        LoadLight(buffer, o);
        DirectionalLight* l = Cast<DirectionalLight*>(o);
        Math::LoadVector3f(buffer, l->m_direction);
        Math::LoadVector3f(buffer, l->m_color);
        l->m_distance = buffer->ReadReal32();
        l->m_energy = buffer->ReadReal32();
    }
}
