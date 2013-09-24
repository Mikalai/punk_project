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

    void SaveAnimation(System::Buffer *buffer, const System::Object *o)
    {
        System::SaveObject(buffer, o);
        const Animation* animation = Cast<const Animation*>(o);
        SaveAnimationTrack(buffer, animation->m_pos_track);
        SaveAnimationTrack(buffer, animation->m_rot_track);
        System::SaveString(buffer, animation->m_name);
    }

    void LoadAnimation(System::Buffer *buffer, System::Object *o)
    {
        System::LoadObject(buffer, o);
        Animation* animation = Cast<Animation*>(o);
        LoadAnimationTrack(buffer, animation->m_pos_track);
        LoadAnimationTrack(buffer, animation->m_rot_track);
        System::LoadString(buffer, animation->m_name);
    }
}
