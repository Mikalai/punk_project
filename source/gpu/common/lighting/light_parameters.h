#ifndef LIGHT_PARAMETERS_H
#define LIGHT_PARAMETERS_H

#include "../../../math/vec4.h"
#include "../../../math/mat4.h"
#include "light_model.h"

namespace Gpu
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

        void SetFarZ(float value);
        float GetFarZ() const;

        void SetNearZ(float value);
        float GetNearZ() const;

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

        const Math::mat4 GetProjectionMatrix() const;
        const Math::mat4 GetViewMatrix() const;

        void SetShadowMatrix(size_t index, const Math::mat4& value);
        const Math::mat4& GetShadowMatrix(size_t index) const;

        void SetFarDistance(size_t index, float value);
        float GetFarDistance(size_t index) const;
        const Math::vec4& GetFarDistances() const;

        void SetSpecularColor(const Math::vec4& value);
        void SetSpecularColor(float r, float y, float b, float a);
        const Math::vec4& GetSpecularColor() const;

        void SetViewDirection(const Math::vec3& value);
        const Math::vec4& GetViewDirection() const;

        void SetViewPosition(const Math::vec3& value);
        const Math::vec4& GetViewPosition() const;

        void SetEnable(bool value);
        bool IsEnabled() const;
        void Enable();
        void Disable();

	private:
		LightType m_light_type;
		LightAttenuation m_attenuation;
		float m_constant_attenuation;
		float m_linear_attenuation;
		float m_quadric_attenuation;
		float m_spot_exponent;
        /// World light position
		Math::vec4 m_position;
        /// World light direction
		Math::vec4 m_direction;
        Math::vec4 m_view_position;
        Math::vec4 m_view_direction;
		Math::vec4 m_diffuse_color;
		Math::vec4 m_ambient_color;
        Math::mat4 m_shadow_matrix[4];
        Math::vec4 m_far_distance;
        Math::vec4 m_specular_color;
        float m_zfar;
        float m_znear;
        bool m_enabled;
	};
}

#endif // LIGHT_PARAMETERS_H
