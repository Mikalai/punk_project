#ifndef _H_PUNK_VIRTUAL_POINT_LIGHT
#define _H_PUNK_VIRTUAL_POINT_LIGHT

#include "../light.h"
#include "../../../string/string.h"
#include <iosfwd>

namespace Utility { class LightDesc; }
namespace Virtual
{
	class PUNK_ENGINE_PUBLIC PointLight : public Light
	{
		Math::vec3 m_position;
		Math::vec3 m_color;
		float m_distance;
		float m_energy;
		float m_linear_attenuation;
		float m_quadratic_attenuation;
	public:

		PointLight();
		PointLight(const Utility::LightDesc& desc);
		virtual ~PointLight();

		virtual const Math::vec3 GetPosition() const;
		virtual void SetPosition(const Math::vec3& value);

		virtual bool Save(std::ostream& stream) const;
		virtual bool Load(std::istream& stream);

		void SetColor(const Math::vec3& value) { m_color = value; }
		const Math::vec3& GetColor() const { return m_color; }

		void SetDistance(float value) { m_distance = value; }
		float GetDistance() const { return m_distance; }

		void SetEnergy(float value) { m_energy = value; }
		float GetEnergy() const { return m_energy; }

		void SetLinearAttenuation(float value) { m_linear_attenuation = value; }
		float GetLinearAttenuation() const { return m_linear_attenuation; }

		void SetQuadraticAttenuation(float value) { m_quadratic_attenuation = value; }
		float GetQuadraticAttenuation() const { return m_quadratic_attenuation; }

		static PointLight* CreateFromFile(const System::string& path);
		static PointLight* CreateFromStream(std::istream& stream);
	};
}

#endif	//	_H_PUNK_VIRTUAL_POINT_LIGHT