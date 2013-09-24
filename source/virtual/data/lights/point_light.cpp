#include <fstream>
#include <memory>
#include "../../../system/buffer.h"
#include "../../../math/vec2.h"
#include "../../../math/vec3.h"
#include "../../../math/vec4.h"
#include "point_light.h"
#include "../../../utility/descriptors/light_desc.h"
#include "../../../engine_objects.h"

namespace Virtual
{
    PUNK_OBJECT_REG(PointLight, "Virtual.PointLight", PUNK_POINT_LIGHT, SavePointLight, LoadPointLight, &Light::Info.Type);

	PointLight::PointLight()
	{
        Info.Add(this);
	}

	PointLight::PointLight(const Utility::LightDesc& value)
		: m_position(Math::vec3())
		, m_color(value.m_color)
		, m_distance(value.m_distance)
		, m_energy(value.m_energy)
		, m_linear_attenuation(value.m_linear_attenuation)
		, m_quadratic_attenuation(value.m_quadratic_attenuation)
	{
        Info.Add(this);
	}

    PointLight::~PointLight()
    {
        Info.Remove(this);
    }

	const Math::vec3 PointLight::GetPosition() const
	{
		return m_position;
	}


//	PointLight* PointLight::CreateFromFile(const System::string& path)
//	{
//		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
//		if (!stream.is_open())
//			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
//		return CreateFromStream(stream);
//	}

//	PointLight* PointLight::CreateFromStream(std::istream& stream)
//	{
//		std::unique_ptr<PointLight> node(new PointLight);
//		node->Load(stream);
//		return node.release();
//	}

	void PointLight::SetPosition(const Math::vec3& value)
	{
		m_position = value;
	}

    void SavePointLight(System::Buffer *buffer, const System::Object *o)
    {
        SaveLight(buffer, o);
        const PointLight* p = Cast<const PointLight*>(o);
        Math::SaveVector3f(buffer, p->m_position);
        Math::SaveVector4f(buffer, p->m_color);
        buffer->WriteReal32(p->m_distance);
        buffer->WriteReal32(p->m_energy);
        buffer->WriteReal32(p->m_linear_attenuation);
        buffer->WriteReal32(p->m_quadratic_attenuation);
    }

    void LoadPointLight(System::Buffer *buffer, System::Object *o)
    {
        SaveLight(buffer, o);
        PointLight* p = Cast<PointLight*>(o);
        Math::LoadVector3f(buffer, p->m_position);
        Math::LoadVector3f(buffer, p->m_color);
        p->m_distance = buffer->ReadReal32();
        p->m_energy = buffer->ReadReal32();
        p->m_linear_attenuation = buffer->ReadReal32();
        p->m_quadratic_attenuation = buffer->ReadReal32();
    }
}
