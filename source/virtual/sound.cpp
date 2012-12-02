#include <istream>
#include <ostream>

#include "sound.h"

namespace Utility
{
	bool Sound::Save(std::ostream& stream) const
	{
		m_name.Save(stream);
		m_filename.Save(stream);
		stream.write((char*)&m_volume, sizeof(m_volume));
		stream.write((char*)&m_pitch, sizeof(m_pitch));
		stream.write((char*)&m_max_distance, sizeof(m_max_distance));
		stream.write((char*)&m_reference_distance, sizeof(m_reference_distance));
		stream.write((char*)&m_cone_angle_inner, sizeof(m_cone_angle_inner));
		stream.write((char*)&m_cone_angle_outer, sizeof(m_cone_angle_outer));
		stream.write((char*)&m_cone_volume_outer, sizeof(m_cone_volume_outer));
		stream.write((char*)&m_attenuation, sizeof(m_attenuation));

		return true;
	}

	bool Sound::Load(std::istream& stream)
	{
		m_name.Load(stream);
		m_filename.Load(stream);
		stream.read((char*)&m_volume, sizeof(m_volume));
		stream.read((char*)&m_pitch, sizeof(m_pitch));
		stream.read((char*)&m_max_distance, sizeof(m_max_distance));
		stream.read((char*)&m_reference_distance, sizeof(m_reference_distance));
		stream.read((char*)&m_cone_angle_inner, sizeof(m_cone_angle_inner));
		stream.read((char*)&m_cone_angle_outer, sizeof(m_cone_angle_outer));
		stream.read((char*)&m_cone_volume_outer, sizeof(m_cone_volume_outer));
		stream.read((char*)&m_attenuation, sizeof(m_attenuation));

		return true;
	}
}