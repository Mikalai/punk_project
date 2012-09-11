#ifndef _H_PUNK_UTILITY_LIGHT
#define _H_PUNK_UTILITY_LIGHT

#include "../config.h"
#include "../math/vec4.h"
#include "../string/string.h"
#include "../utility/decl_property.h"

namespace Utility
{
	class PUNK_ENGINE Light
	{
	public:		
		virtual void Save(std::ostream& stream) {};
		virtual void Load(std::istream& stream) {};		

		static Light* LoadFromStream(std::istream& stream);
	};

	class PUNK_ENGINE PointLight : public Light
	{
	public:

		PROPERTY(System::string, Type, m_type);
		PROPERTY(System::string, Name, m_name);		
		PROPERTY(Math::vec4, Color, m_color);
		PROPERTY(float, Distance, m_distance);
		PROPERTY(float, Energy, m_energy);
		PROPERTY(System::string, FalloffType, m_falloff_type);
		PROPERTY(float, LinearAttenuation, m_linear_attenuation);
		PROPERTY(float, QuadraticAttenuation, m_quadratic_attenuation);

		virtual void Save(std::ostream& stream);
		virtual void Load(std::istream& stream);

	private:

		System::string m_type;
		System::string m_name;		
		Math::vec4 m_color;
		float m_distance;
		float m_energy;
		System::string m_falloff_type;
		float m_linear_attenuation;
		float m_quadratic_attenuation;
	};
}

#endif	//	_H_PUNK_UTILITY_LIGHT