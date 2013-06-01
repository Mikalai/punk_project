#include <fstream>
#include <memory>
#include "point_light.h"
#include "../../../utility/descriptors/light_desc.h"

namespace Virtual
{
	PointLight::PointLight()
	{
		SetType(System::ObjectType::POINT_LIGHT);
	}

	PointLight::PointLight(const Utility::LightDesc& value)
		: m_position(Math::vec3())
		, m_color(value.m_color)
		, m_distance(value.m_distance)
		, m_energy(value.m_energy)
		, m_linear_attenuation(value.m_linear_attenuation)
		, m_quadratic_attenuation(value.m_quadratic_attenuation)
	{
		SetStorageName(value.m_name);
		SetType(System::ObjectType::POINT_LIGHT);
	}

	PointLight::~PointLight() {}

	const Math::vec3 PointLight::GetPosition() const
	{
		return m_position;
	}

	bool PointLight::Save(std::ostream& stream) const
	{
		Light::Save(stream);
		m_position.Save(stream);
		m_color.Save(stream);
		stream.write((char*)&m_distance, sizeof(m_distance));
		stream.write((char*)&m_energy, sizeof(m_energy));
		stream.write((char*)&m_linear_attenuation, sizeof(m_linear_attenuation));
		stream.write((char*)&m_quadratic_attenuation, sizeof(m_quadratic_attenuation));
		return true;
	}

	bool PointLight::Load(std::istream& stream)
	{
		Light::Load(stream);
		m_position.Load(stream);
		m_color.Load(stream);
		stream.read((char*)&m_distance, sizeof(m_distance));
		stream.read((char*)&m_energy, sizeof(m_energy));
		stream.read((char*)&m_linear_attenuation, sizeof(m_linear_attenuation));
		stream.read((char*)&m_quadratic_attenuation, sizeof(m_quadratic_attenuation));
		return true;
	}

	PointLight* PointLight::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
		if (!stream.is_open())
			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
		return CreateFromStream(stream);
	}

	PointLight* PointLight::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<PointLight> node(new PointLight);
		node->Load(stream);
		return node.release();
	}

	void PointLight::SetPosition(const Math::vec3& value)
	{
		m_position = value;
	}
}
