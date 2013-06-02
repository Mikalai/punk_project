#ifndef _H_PUNK_UTILITY_SOUND
#define _H_PUNK_UTILITY_SOUND

#include "../config.h"
#include "../math/vec3.h"
#include "../string/string.h"
#include "../system/decl_property.h"

#include <iosfwd>

namespace Utility
{
	class PUNK_ENGINE_API Sound
	{
	public:
		PROPERTY(System::string, Name, m_name);
		PROPERTY(System::string, Filename, m_filename);
		PROPERTY(float, Volume, m_volume);
		PROPERTY(float, Pitch, m_pitch);
		PROPERTY(float, MaxDistance, m_max_distance);
		PROPERTY(float, ReferenceDistance, m_reference_distance);
		PROPERTY(float, ConeAngleInner, m_cone_angle_inner);
		PROPERTY(float, ConeAngleOuter, m_cone_angle_outer);
		PROPERTY(float, ConeVolumeOuter, m_cone_volume_outer);
		PROPERTY(float, Attenuation, m_attenuation);
		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);
	private:
		System::string m_name;
		System::string m_filename;
		float m_volume;
		float m_pitch;
		float m_max_distance;
		float m_reference_distance;
		float m_cone_angle_inner;
		float m_cone_angle_outer;
		float m_cone_volume_outer;
		float m_attenuation;
	};
}

#endif