#include "light.h"
#include "../system/logger.h"

#include <ostream>
#include <istream>

namespace Utility
{
	Light* Light::LoadFromStream(std::istream& stream)
	{
		System::string s;
		s.Load(stream);
		if (s == L"POINT")
		{
			std::auto_ptr<PointLight> light(new PointLight);
			light->SetType(s);
			s.Load(stream);
			light->SetName(s);
			Math::vec4 v;
			v.Load(stream);
			light->SetColor(v);
			float f;
			stream.read((char*)&f, sizeof(f));
			light->SetDistance(f);
			stream.read((char*)&f, sizeof(f));
			light->SetEnergy(f);
			s.Load(stream);
			light->SetFalloffType(s);
			stream.read((char*)&f, sizeof(f));
			light->SetLinearAttenuation(f);
			stream.read((char*)&f, sizeof(f));
			light->SetQuadraticAttenuation(f);
			return light.release();
		}
		else
		{
			out_error() << L"Unsupported light type: " << s << std::endl;
		}
	}

	void PointLight::Save(std::ostream& stream)
	{
		m_type.Save(stream);
		m_name.Save(stream);		
		m_color.Save(stream);
		stream.write((char*)&m_distance, sizeof(m_distance));
		stream.write((char*)&m_energy, sizeof(m_energy));
		m_falloff_type.Save(stream);
		stream.write((char*)&m_linear_attenuation, sizeof(m_linear_attenuation));
		stream.write((char*)&m_quadratic_attenuation, sizeof(m_quadratic_attenuation));
	}

	void PointLight::Load(std::istream& stream)
	{
		m_type.Load(stream);
		m_name.Load(stream);		
		m_color.Load(stream);
		stream.read((char*)&m_distance, sizeof(m_distance));
		stream.read((char*)&m_energy, sizeof(m_energy));
		m_falloff_type.Load(stream);
		stream.read((char*)&m_linear_attenuation, sizeof(m_linear_attenuation));
		stream.read((char*)&m_quadratic_attenuation, sizeof(m_quadratic_attenuation));
	}
}
