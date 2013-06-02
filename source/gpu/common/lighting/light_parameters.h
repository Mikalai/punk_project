#ifndef LIGHT_PARAMETERS_H
#define LIGHT_PARAMETERS_H

#include "../../../math/vec4.h"
#include "light_model.h"

namespace GPU
{
	class PUNK_ENGINE_API LightParameters
	{
	public:
		LightParameters();

		void SetPosition(float x, float y, float z);
		void SetPosition(const Math::vec3& value);
		const Math::vec4& GetPosition() const;

		void SetDirection(float x, float y, float z);
		void SetDirection(const Math::vec3& value);
		const Math::vec4& GetDirection() const;

		void SetDiffuseColor(float r, float g, float b, float a);
		void SetDiffuseColor(const Math::vec4& value);
		const Math::vec4& GetDiffuseColor() const;

		void SetAmbientColor(float r, float g, float b, float a);
		void SetAmbientColor(const Math::vec4& value);
		const Math::vec4& GetAmbientColor() const;

		void SetLightAttenuation(LightAttenuation value);
		LightAttenuation GetLightAttenuation() const;

		void SetLightConstantAttenuation(float value);
		float GetLightConstantAttenuation() const;

		void SetLightLinearAttenuation(float value);
		float GetLightLinearAttenuation() const;

		void SetLightQuadricAttenuation(float value);
		float GetLightQuadricAttenuation() const;

		void SetType(LightType value);
		LightType GetType() const;

		void SetSpotExponent(float value);
		float GetSpotExponent() const;

	private:
		LightType m_light_type;
		LightAttenuation m_attenuation;
		float m_constant_attenuation;
		float m_linear_attenuation;
		float m_quadric_attenuation;
		float m_spot_exponent;
		Math::vec4 m_position;
		Math::vec4 m_direction;
		Math::vec4 m_diffuse_color;
		Math::vec4 m_ambient_color;
	};
}

#endif // LIGHT_PARAMETERS_H
