#include "light_parameters.h"

namespace GPU
{

	LightParameters::LightParameters()
	{
		m_attenuation = LightAttenuation::Constant;
		m_constant_attenuation = 1;
		m_linear_attenuation = 0;
		m_quadric_attenuation = 0;
		m_spot_exponent = 100.0;
	}

	void LightParameters::SetPosition(float x, float y, float z)
	{
		m_position.Set(x, y, z, 1);
	}

	void LightParameters::SetPosition(const Math::vec3& value)
	{
		m_position.Set(value[0], value[1], value[2], 1);
	}

	const Math::vec4& LightParameters::GetPosition() const
	{
		return m_position;
	}

	void LightParameters::SetDirection(float x, float y, float z)
	{
		m_direction.Set(x, y, z, 0);
	}

	void LightParameters::SetDirection(const Math::vec3& value)
	{
		m_direction.Set(value[0], value[1], value[2], 0);
	}

	const Math::vec4& LightParameters::GetDirection() const
	{
		return m_direction;
	}

	void LightParameters::SetDiffuseColor(float r, float g, float b, float a)
	{
		m_diffuse_color.Set(r, g, b, a);
	}

	void LightParameters::SetDiffuseColor(const Math::vec4& value)
	{
		m_diffuse_color = value;
	}

	const Math::vec4& LightParameters::GetDiffuseColor() const
	{
		return m_diffuse_color;
	}

	void LightParameters::SetAmbientColor(float r, float g, float b, float a)
	{
		m_ambient_color.Set(r, g, b, a);
	}

	void LightParameters::SetAmbientColor(const Math::vec4& value)
	{
		m_ambient_color = value;
	}

	const Math::vec4& LightParameters::GetAmbientColor() const
	{
		return m_ambient_color;
	}

	void LightParameters::SetLightAttenuation(LightAttenuation value)
	{
		m_attenuation = value;
	}

	LightAttenuation LightParameters::GetLightAttenuation() const
	{
		return m_attenuation;
	}

	void LightParameters::SetLightConstantAttenuation(float value)
	{
		m_constant_attenuation = value;
	}

	float LightParameters::GetLightConstantAttenuation() const
	{
		return m_constant_attenuation;
	}

	void LightParameters::SetLightLinearAttenuation(float value)
	{
		m_linear_attenuation = value;
	}

	float LightParameters::GetLightLinearAttenuation() const
	{
		return m_linear_attenuation;
	}

	void LightParameters::SetLightQuadricAttenuation(float value)
	{
		m_quadric_attenuation = value;
	}

	float LightParameters::GetLightQuadricAttenuation() const
	{
		return m_quadric_attenuation;
	}

	void LightParameters::SetType(LightType value)
	{
		m_light_type = value;
	}

	LightType LightParameters::GetType() const
	{
		return m_light_type;
	}

	void LightParameters::SetSpotExponent(float value)
	{
		m_spot_exponent = value;
	}

	float LightParameters::GetSpotExponent() const
	{
		return m_spot_exponent;
	}
}
