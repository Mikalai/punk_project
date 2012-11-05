#include <ostream>
#include <istream>
#include "../../utility/descriptors/animation_desc.h"
#include "animation.h"

namespace Virtual
{
	Animation::Animation()
		: m_animation_type(AnimationType::NONE)
	{
	}

	Animation::Animation(Utility::AnimationDesc& desc)
	{
		m_animation_type = (desc.m_is_bone_anim) ? AnimationType::BONE : AnimationType::OBJECT;
		m_pos_track = desc.m_pos_track;
		m_rot_track = desc.m_rot_track;
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

	bool Animation::Save(std::ostream& stream)
	{
		//stream.write(reinterpret_cast<const char*>(&m_is_enabled), sizeof(m_is_enabled));		
		stream.write((char*)&m_animation_type, sizeof(m_animation_type));
		m_pos_track.Save(stream);
		m_rot_track.Save(stream);
		return true;
	}

	bool Animation::Load(std::istream& stream)
	{
		//stream.read(reinterpret_cast<char*>(&m_is_enabled), sizeof(m_is_enabled));		
		stream.read((char*)&m_animation_type, sizeof(m_animation_type));
		m_pos_track.Load(stream);
		m_rot_track.Load(stream);
		return true;
	}
}
