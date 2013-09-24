#include "../../../system/buffer.h"
#include "sun.h"
#include "../../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(Sun, "Virtual.Sun", PUNK_SUN, SaveSun, LoadSun, &System::Object::Info.Type);

    Sun::Sun()
    {
        Info.Add(this);
    }

    Sun::~Sun()
    {
        Info.Remove(this);
    }

    void Sun::SetEnergy(float value)
    {
        m_energy = value;
    }

    float Sun::GetEnergy() const
    {
        return m_energy;
    }

    void Sun::SetColor(const Math::vec3& value)
    {
        m_color = value;
    }

    const Math::vec3& Sun::GetColor() const
    {
        return m_color;
    }

    void Sun::SetName(const System::string& value)
    {
        m_name = value;
    }

    const System::string& Sun::GetName() const
    {
        return m_name;
    }

    void SaveSun(System::Buffer *buffer, const System::Object *o)
    {
        System::SaveObject(buffer, o);
        const Sun* s = Cast<const Sun*>(o);
        buffer->WriteReal32(s->m_energy);
        Math::SaveVector3f(buffer, s->m_color);
        System::SaveString(buffer, s->m_name);
    }

    void LoadSun(System::Buffer *buffer, System::Object *o)
    {
        System::LoadObject(buffer, o);
        Sun* s = Cast<Sun*>(o);
        s->m_energy = buffer->ReadReal32();
        Math::LoadVector3f(buffer, s->m_color);
        System::LoadString(buffer, s->m_name);
    }
}
