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

	bool Animation::Save(std::ostream& stream) const
	{
		System::Object::Save(stream);

		m_pos_track.Save(stream);
		m_rot_track.Save(stream);
		return true;
	}

	bool Animation::Load(std::istream& stream)
	{
		System::Object::Load(stream);

		m_pos_track.Load(stream);
		m_rot_track.Load(stream);
		return true;
	}

	Animation* Animation::CreateFromFile(const System::string& path)
	{
		std::ifstream stream(path.Data(), std::ios::binary);
		stream.is_open();
		return CreateFromStream(stream);
	}

	Animation* Animation::CreateFromStream(std::istream& stream)
	{
		std::unique_ptr<Animation> node(new Animation);
		node->Load(stream);
		return node.release();
	}
}
