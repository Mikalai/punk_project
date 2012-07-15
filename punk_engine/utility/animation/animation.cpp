#include <ostream>
#include <istream>
#include "animation.h"

namespace Utility
{
	Animation::Animation()
	{
		m_pos_track.SetLooping(true);
		m_rot_track.SetLooping(true);
	}

	void Animation::AddPositionKey(int frame, Math::Vector3<float>& position)
	{
		m_pos_track.AddKey(frame, position);
	}
		
	void Animation::AddRotationKey(int frame, Math::Quaternion<float>& rotation)
	{
		m_rot_track.AddKey(frame, rotation);
	}
		
	Math::Vector3<float>& Animation::GetOrCreatePositionKey(int time)
	{
		if (!m_pos_track.HasKeyAt(time))
			m_pos_track.AddKey(time, Math::vec3());
		bool flag;
		return m_pos_track.GetOriginalKey(time, flag);
	}

	Math::Quaternion<float>& Animation::GetOrCreateRotationKey(int time)
	{
		if (!m_rot_track.HasKeyAt(time))
			m_rot_track.AddKey(time, Math::quat());
		bool flag;
		return m_rot_track.GetOriginalKey(time, flag);
	}

	const Math::Vector3<float> Animation::GetPosition(float time)
	{
		return m_pos_track.GetKey(time);
	}
		
	const Math::Quaternion<float> Animation::GetRotation(float time)
	{
		return m_rot_track.GetKey(time);
	}

	void Animation::Enable(bool flag)
	{
		m_is_enabled = flag;
	}

	bool Animation::IsEnabled() const
	{
		return m_is_enabled;
	}

	void Animation::SetLooping(bool flag)
	{
		m_pos_track.SetLooping(flag);
		m_rot_track.SetLooping(flag);
	}
	
	bool Animation::IsLooping() const
	{
		return m_pos_track.IsLooping();
	}

	void Animation::Save(std::ostream& stream)
	{
		stream.write(reinterpret_cast<const char*>(&m_is_enabled), sizeof(m_is_enabled));		

		m_pos_track.Save(stream);
		m_rot_track.Save(stream);
	}

	void Animation::Load(std::istream& stream)
	{
		stream.read(reinterpret_cast<char*>(&m_is_enabled), sizeof(m_is_enabled));		
		m_pos_track.Load(stream);
		m_rot_track.Load(stream);
	}
}
