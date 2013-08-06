 #include <ostream>
#include <istream>
#include "animation.h"

namespace Virtual
{
	Animation::Animation()
	{
	}

	void Animation::AddPositionKey(int frame, Math::vec3& position)
	{
		m_pos_track.AddKey(frame, position);
	}

	void Animation::AddRotationKey(int frame, Math::quat& rotation)
	{
		m_rot_track.AddKey(frame, rotation);
	}

	Math::vec3& Animation::GetOrCreatePositionKey(int time)
	{
		if (!m_pos_track.HasKeyAt(time))
			m_pos_track.AddKey(time, Math::vec3());
		bool flag;
		return m_pos_track.GetOriginalKey(time, flag);
	}

	Math::quat& Animation::GetOrCreateRotationKey(int time)
	{
		if (!m_rot_track.HasKeyAt(time))
			m_rot_track.AddKey(time, Math::quat());
		bool flag;
		return m_rot_track.GetOriginalKey(time, flag);
	}

	const Math::vec3 Animation::GetPosition(float time) const
	{
		return m_pos_track.GetKey(time);
	}

	const Math::quat Animation::GetRotation(float time) const
	{
		return m_rot_track.GetKey(time);
    }

    const System::string& Animation::GetName() const
    {
        return m_name;
    }

    void Animation::SetName(const System::string& value)
    {
        m_name = value;
    }

    void Animation::Save(System::Buffer* buffer) const
    {
        Object::Save(buffer);
        m_pos_track.Save(buffer);
        m_rot_track.Save(buffer);
        buffer->WriteString(m_name);
    }

    void Animation::Load(System::Buffer* buffer)
    {
        Object::Load(buffer);
        m_pos_track.Load(buffer);
        m_rot_track.Load(buffer);
        m_name = buffer->ReadString();
    }
}
