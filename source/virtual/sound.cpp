#include <istream>
#include <ostream>
#include "../system/buffer.h"
#include "sound.h"

namespace Virtual
{
    void Sound::Save(System::Buffer *buffer) const
	{
        buffer->WriteString(m_name);
        buffer->WriteString(m_filename);
        buffer->WriteReal32(m_volume);
        buffer->WriteReal32(m_pitch);
        buffer->WriteReal32(m_max_distance);
        buffer->WriteReal32(m_reference_distance);
        buffer->WriteReal32(m_cone_angle_inner);
        buffer->WriteReal32(m_cone_angle_outer);
        buffer->WriteReal32(m_cone_volume_outer);
        buffer->WriteReal32(m_attenuation);
	}

    void Sound::Load(System::Buffer *buffer)
	{
        m_name = buffer->ReadString();
        m_filename = buffer->ReadString();
        m_volume = buffer->ReadReal32();
        m_pitch = buffer->ReadReal32();
        m_max_distance = buffer->ReadReal32();
        m_reference_distance = buffer->ReadReal32();
        m_cone_angle_inner = buffer->ReadReal32();
        m_cone_angle_outer = buffer->ReadReal32();
        m_cone_volume_outer = buffer->ReadReal32();
        m_attenuation = buffer->ReadReal32();
	}
}
